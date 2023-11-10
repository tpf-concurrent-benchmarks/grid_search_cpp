EXEC_MASTER = master-gs
EXEC_WORKER = worker-gs
N_WORKERS = 4

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

init:
	docker swarm init

build:
	docker rmi grid_search_cpp_worker -f
	docker rmi grid_search_cpp_manager -f
	docker build -t grid_search_cpp_worker ./src/ -f ./src/worker/Dockerfile
	docker build -t grid_search_cpp_manager ./src/ -f ./src/master/Dockerfile

setup: init build

deploy:
	mkdir -p graphite
	docker compose -f=docker-compose-deploy-local.yml up

deploy_remote:
	mkdir -p graphite
	docker stack deploy -c docker-compose-deploy.yml gs_cpp

remove:
	docker stack rm gs_cpp

manager_logs:
	docker service logs -f gs_cpp_manager

full_build_master_local:
	cd src/master/ && mkdir -p cmake-build-debug && cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=Release ..  && cmake --build .

build_master_local:
	cd src/master/cmake-build-debug && cmake --build .

run_master_local:
	cd src/master/cmake-build-debug && ENV=LOCAL ./${EXEC_MASTER}

full_build_worker_local:
	cd src/worker/ && mkdir -p cmake-build-debug && cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

build_worker_local:
	cd src/worker/cmake-build-debug && cmake --build .

run_worker_local:
	cd src/worker/cmake-build-debug && ENV=LOCAL ./$(EXEC_WORKER)

valgrind_master:
	cd src/master/cmake-build-debug  && valgrind $(VFLAGS) ./$(EXEC_MASTER)

valgrind_worker:
	cd src/worker/cmake-build-debug && valgrind $(VFLAGS) ./$(EXEC_WORKER)

format:
	clang-format -i src/master/src/**/*.cpp src/master/src/**/*.h src/worker/src/**/*.cpp src/worker/src/**/*.h
	clang-format -i src/master/src/main.cpp src/worker/src/main.cpp
	clang-format -i src/shared/*.h

run_graphite: down_graphite
	docker stack deploy -c docker-compose-graphite.yaml graphite
.PHONY: run_graphite

down_graphite:
	if docker stack ls | grep -q graphite; then \
		docker stack rm graphite; \
		docker stack rm grafana; \
		docker stack rm cadvisor; \
	fi
.PHONY: down_graphite
