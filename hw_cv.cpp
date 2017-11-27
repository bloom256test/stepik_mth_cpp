#include <iostream>
#include <pthread.h>

pthread_barrier_t barrier;
pthread_mutex_t mutex;
pthread_cond_t cv;

void* wait_cv(void*)
{
	std::cout << "locking mutex" << std::endl;
	pthread_mutex_lock(&mutex);
	std::cout << "waiting cv" << std::endl;
	pthread_cond_wait(&cv, &mutex);
	std::cout << "exiting thread 1" << std::endl;
	pthread_exit(nullptr);
}

void* wait_barrier(void*)
{
	std::cout << "waiting barrier" << std::endl;
	pthread_barrier_wait(&barrier);
	std::cout << "exiting thread 2" << std::endl;
	pthread_exit(nullptr);
}

int main(int argc, char** argv)
{
	std::cout << "hw_cv" << std::endl;
	std::cout << "self " << pthread_self() << std::endl;

	pthread_mutex_init(&mutex, nullptr);
	pthread_cond_init (&cv, nullptr);
	pthread_barrier_init(&barrier, nullptr, 10);

	std::cout << "creating threads" << std::endl;
	pthread_t thread1, thread2;
	pthread_create(&thread1, nullptr, wait_cv, nullptr);
	pthread_create(&thread2, nullptr, wait_barrier, nullptr);

	std::cout << "waiting threads" << std::endl;
	pthread_join(thread1, nullptr);
	std::cout << "got thread 1" << std::endl;
	pthread_join(thread2, nullptr);
	std::cout << "got thread 2" << std::endl;

	exit(0);
}
