//#include<thread>
//#include<chrono>
//#include<condition_variable>
//#include<mutex>
//#include<iostream>
//using namespace std::chrono;
//std::mutex mtx;
//std::condition_variable cv;
//bool flag = true;
//int n = 100;
//int main()
//{
//    std::thread t1([&]() {
//        int i = 0;
//        
//        while (i <= n)
//        {
//            std::unique_lock<std::mutex> lock(mtx);
//            while (!flag)
//            {
//                cv.wait(lock);
//            }
//            
//            std::cout << i << std::endl;
//            flag = false;
//            i += 2;
//            cv.notify_one();
//        }
//    });//´òÓ¡Å¼Êý
//    std::thread t2([&]() {
//        int j = 1;
//        while (j < n) {
//            std::unique_lock<std::mutex> lock(mtx);
//            while (flag) {
//                cv.wait(lock);
//            }
//            std::cout << j << std::endl;
//            flag = true;
//            j += 2;
//            cv.notify_one();
//        }
//    });
//    t1.join();
//    t2.join();
//    
//}
