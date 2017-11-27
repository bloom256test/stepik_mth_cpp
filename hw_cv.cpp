#include <iostream>
#include <pthread.h>

pthread_barrier_t barrier;
pthread_mutex_t mutex;
pthread_cond_t cv;

void* wait_cv(void*)
{
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cv, &mutex);
}

void* wait_barrier(void*)
{
	pthread_barrier_wait(&barrier);
}

int main(int argc, char** argv)
{
	std::cout << "hw_cv" << std::endl;

	pthread_mutex_init(&mutex, nullptr);
	pthread_cond_init (&cv, nullptr);
	pthread_barrier_init(&barrier, nullptr, 10);

	std::cout << "creating threads" << std::endl;
	pthread_t thread1, thread2;
	pthread_create(&thread1, nullptr, wait_cv, nullptr);
	pthread_create(&thread2, nullptr, wait_barrier, nullptr);

	std::cout << "waiting threads" << std::endl;
	pthread_join(thread1, nullptr);
	pthread_join(thread2, nullptr);

	exit(0);
}
