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
	docker stack deploy -c docker-compose-dev.yml gs_cpp

remove:
	docker stack rm gs_cpp

manager_logs:
	docker service logs -f gs_cpp_manager