#include <bits/stdc++.h>
#include <arm_neon.h>
#include <atomic>

using namespace std;

#define MAT_SIZE 2048
#define TILE_SIZE 256
int A[MAT_SIZE][MAT_SIZE];
int B[MAT_SIZE][MAT_SIZE];
int C[MAT_SIZE][MAT_SIZE];


template <typename Task_type>
class ThreadPool{

	vector<thread> pool;
	queue<Task_type> task_queue;
	int thread_count;
	bool running = 0;
	atomic_flag lock_queue = ATOMIC_FLAG_INIT;

public:
	bool finished = 0;

	ThreadPool(int tc = 32){
		this->thread_count = tc;
	}

	void t_init(){
		bool die = 0;
		while(true){
			while (lock_queue.test_and_set(memory_order_acquire)) {} // SPIN
											            // CRITICAL SECTION BEGIN
			Task_type top_task;
			bool assigned = 0;
			if (!task_queue.empty()){
				top_task = task_queue.front();
				task_queue.pop();
				assigned = 1;
			} 
			else if (finished) die = 1;

			lock_queue.clear(memory_order_release);     // CRITICAL SECTION END

			if(assigned) ThreadPool::run(top_task);
			if(die) break;
		}
	}

	void addTask(Task_type task){
		if(running){
			while (lock_queue.test_and_set(memory_order_acquire)) {}
			task_queue.push(task);
			lock_queue.clear(memory_order_release); 
		} 
		else task_queue.push(task);
	}

	void runAll(){
		this->running = 1;
		for(int i=0; i<this->thread_count; ++i) pool.push_back(thread(&ThreadPool::t_init, this));
	}

	void run(Task_type task){
        int res[4];
        int32x4_t vec1, vec2, ansV;

		for(int i=0; i<TILE_SIZE; ++i)
			for(int j=0; j<TILE_SIZE; ++j)
                for (int k = 0; k < MAT_SIZE; k += 4) {
                    // Load 4 elements from array1 and array2
                    vec1 = vld1q_s32(&A[i][k]);
                    vec2 = vld1q_s32(&B[j][k]);
                    // Store the result back to the result array
                    vst1q_s32(&res[0], vmlaq_s32(ansV, vec1, vec2));
                    C[i+task.first][j+task.second] += res[0]+res[1]+res[2]+res[3];
                }
	}

	void joinall() {
        for (auto& thread : pool) thread.join();
    }
};

int main(){
	#ifndef ONLINE_JUDGE
	freopen("./outputs/input.txt", "r", stdin);
    freopen("./outputs/tiled_simd_thread_output.txt", "w", stdout);
    #endif

	auto start = chrono::high_resolution_clock::now();

	ThreadPool<pair<int,int>> tp(8);
	// tp.runAll();

    for(int i=0; i<MAT_SIZE; ++i)
        for(int j=i+1; j<MAT_SIZE; ++j)
            swap(B[i][j], B[j][i]);

    for(int tx=0; tx < MAT_SIZE/TILE_SIZE; ++tx){
        for(int ty=0; ty < MAT_SIZE/TILE_SIZE; ++ty){
            tp.addTask({tx, ty});
        }
    }
	tp.runAll();

	tp.finished = 1;
	tp.joinall();

	auto stop = chrono::high_resolution_clock::now();

	cout << "MATRIX SIZE :: " << MAT_SIZE << endl;
	cout << "TILED NO THREADING, LOOP ORDER :: " << "j k i" << endl;
	cout << "EXECUTION TIME :: " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " µs";
	cout << "\n======================\n\n";

	return 0;
}