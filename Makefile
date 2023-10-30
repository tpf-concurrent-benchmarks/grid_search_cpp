EXEC_MASTER = master-gs
EXEC_WORKER = worker-gs

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

init:
	docker swarm init

build:
	docker rmi grid_search_cpp_worker -f
	docker rmi grid_search_cpp_manager -f
	docker build -t grid_search_cpp_worker ./src/worker/
	docker build -t grid_search_cpp_manager ./src/master/

build_rabbitmq:
	docker build -t rostov_rabbitmq ./src/rabbitmq/

setup: init build build_rabbitmq

deploy:
	docker stack deploy -c docker-compose.yml gs_cpp

remove:
	docker stack rm gs_cpp

manager_logs:
	docker service logs -f gs_cpp_manager

full_build_master_local:
	cd src/master/ && mkdir -p cmake-build-debug && cd cmake-build-debug && cmake .. -DAMQP-CPP_LINUX_TCP=ON && cmake --build .

build_master_local:
	cd src/master/cmake-build-debug && cmake --build .

run_master_local:
	cd src/master/cmake-build-debug && ./${EXEC_MASTER}

full_build_worker_local:
	cd src/worker/ && mkdir -p cmake-build-debug && cd cmake-build-debug && cmake .. -DAMQP-CPP_LINUX_TCP=ON && cmake --build .

build_worker_local:
	cd src/worker/cmake-build-debug && cmake --build .

run_worker_local:
	cd src/worker/cmake-build-debug && ./$(EXEC_WORKER)

valgrind_master:
	valgrind $(VFLAGS) ./src/master/cmake-build-debug/$(EXEC_MASTER)

valgrind_worker:
	valgrind $(VFLAGS) ./src/worker/cmake-build-debug/$(EXEC_WORKER)


format:
	clang-format -i src/master/src/*.cpp src/master/src/*.h src/worker/src/*.cpp src/worker/src/*.h