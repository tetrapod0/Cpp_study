#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

bool ready = false;
bool fin = false;  // 모든 worker가 종료될 때까지 대기하는 플래그
int workers_done = 0;  // 종료된 worker 수를 추적

void notifier(std::mutex* m, std::condition_variable* cv) {
    {
        std::lock_guard<std::mutex> lock(*m);
        ready = true;
        cv->notify_one();  // 하나의 worker에게 알림
    }
}

void worker(std::mutex* m, std::condition_variable* cv) {
    std::unique_lock<std::mutex> lock(*m);
    cv->wait(lock, [] {return ready || fin;});  // ready가 true가 되거나 fin이 true가 되면 대기 해제

    if (ready) {
        std::cout << "Worker processing...\n";
    }
    ready = false;  // 다음 worker를 위해 ready를 false로 설정

    // 모든 worker가 끝났다면 fin을 true로 설정하고 종료
    {
        std::lock_guard<std::mutex> lock(*m);
        workers_done++;
        if (workers_done == 3) {  // 3개의 worker가 모두 종료되면
            fin = true;
            cv->notify_all();  // 모든 worker에게 종료 신호를 보냄
        }
    }
}

int main() {
    std::mutex mtx;
    std::condition_variable cv;

    std::vector<std::thread> worker_threads;
    std::vector<std::thread> notifier_threads;

    //// 3개의 worker 스레드 생성
    //for (int i = 0; i < 3; ++i) {
    //    worker_threads.push_back(std::thread(worker, &mtx, &cv));
    //}

    //// 3개의 notifier 스레드 생성
    //for (int i = 0; i < 3; ++i) {
    //    notifier_threads.push_back(std::thread(notifier, &mtx, &cv));
    //}

    //// 모든 스레드가 종료될 때까지 대기
    //for (auto& t : worker_threads) {
    //    t.join();
    //}
    //for (auto& t : notifier_threads) {
    //    t.join();
    //}

    std::cout << "All workers finished.\n";

    return 0;
}
