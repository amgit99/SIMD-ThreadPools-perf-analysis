#include <bits/stdc++.h>
#include <atomic>

using namespace std;

const int MAT_SIZE = 2048;
int TILE_SIZE = 512;
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
		for(int i=0; i<TILE_SIZE; ++i)
			for(int k=0; k<MAT_SIZE; ++k)
				for(int j=0; j<TILE_SIZE; ++j)
					C[i+task.first][j+task.second] = A[i+task.first][k] * B[k][j+task.second];
	}

	void joinall() {
        for (auto& thread : pool) thread.join();
    }
};

int main(int argc, char* argv[]){
	#ifndef ONLINE_JUDGE
	freopen("./outputs/input.txt", "r", stdin);
    freopen("./outputs/tiled_thread_output.txt", "a", stdout);
    #endif

	TILE_SIZE = stoi(argv[1]);

	ThreadPool<pair<int,int>> tp(8);
	// tp.runAll();

    for(int tx=0; tx < MAT_SIZE/TILE_SIZE; ++tx){
        for(int ty=0; ty < MAT_SIZE/TILE_SIZE; ++ty){
            tp.addTask({tx, ty});
        }
    }
	auto start = chrono::high_resolution_clock::now();
	tp.runAll();

	tp.finished = 1;
	tp.joinall();

	auto stop = chrono::high_resolution_clock::now();

	cout << "MATRIX SIZE :: " << MAT_SIZE << endl;
	cout << "TILE SIZE :: " << TILE_SIZE << endl;
	cout << "TILED WITH THREADING, LOOP ORDER :: " << "j k i" << endl;
	cout << "EXECUTION TIME :: " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " µs";
	cout << "\n======================\n\n";

	return 0;
}