# Docker Notes

## Dockerfile Commands

| Command                           | Description                                               |
| --------------------------------- | --------------------------------------------------------- |
| `FROM [base image]`               | Set the base image for the Dockerfile.                    |
| `MAINTAINER [maintainer name]`    | Set the maintainer of the Dockerfile.                     |
| `RUN [command]`                   | Run a command during the build process.                   |
| `ADD [source] [destination]`      | Copy files from the build context to the container.       |
| `COPY [source] [destination]`     | Copy files from the build context to the container.       |
| `CMD [command]`                   | Set the default command to run when the container starts. |
| `ENTRYPOINT [command]`            | Set the entry point for the container.                    |

## Image Commands

| Command                                                   | Description                             |
| --------------------------------------------------------- | --------------------------------------- |
| `docker image ls`                                         | List all available images.              |
| `docker image rm [image ID]`                              | Remove an image.                        |
| `docker image build -t [image name] [path to Dockerfile]` | Build a Docker image from a Dockerfile. |
| `docker image push [image name]`                          | Push an image to a remote registry.     |
| `docker image pull [image name]`                          | Pull an image from a remote registry.   |

Save and Load

```{sh}
docker load < archive.tar.gz
docker save repository/name:latest > archive.tar
```

## Docker Compose Commands

| Command                                  | Description                                                         |
| ---------------------------------------- | ------------------------------------------------------------------- |
| `docker-compose up`                      | Start all containers defined in the Docker Compose file.            |
| `docker-compose down`                    | Stop and remove all containers defined in the Docker Compose file.  |
| `docker-compose ps`                      | List all containers defined in the Docker Compose file.             |
| `docker-compose logs [service]`          | Display logs for a service in the Docker Compose file.              |
| `docker-compose build`                   | Build all images defined in the Docker Compose file.                |
| `docker-compose config`                  | Validate and view the Docker Compose file.                          |
| `docker-compose run [service] [command]` | Run a command in a new container for a service.                     |

## Containers Commands

| Command                                           | Description                                       |
| ------------------------------------------------- | ------------------------------------------------- |
| `docker container ls`                             | List all running containers.                      |
| `docker container ls -a`                          | List all containers, including stopped ones.      |
| `docker container rm [Container ID]`              | Remove a container.                               |
| `docker container stop [Container ID]`            | Stop a container.                                 |
| `docker container start [Container ID]`           | Start a stopped container.                        |
| `docker container restart [Container ID]`         | Restart a running container.                      |
| `docker container pause [Container ID]`           | Pause a running container.                        |
| `docker container unpause [Container ID]`         | Unpause a paused container.                       |
| `docker container logs [Container ID]`            | Display logs for a container.                     |
| `docker container exec [Container ID] [command]`  | Execute a command inside a running container.     |
| `docker container inspect [Container ID]`         | Display detailed information about a container.   |

## Networks Commands

| Command                                                   | Description                            |
| --------------------------------------------------------- | -------------------------------------- |
| `docker network ls`                                       | List all available networks.           |
| `docker network create [network name]`                    | Create a new Docker network.           |
| `docker network rm [network name]`                        | Remove a Docker network.               |
| `docker network connect [network name] [Container ID]`    | Connect a container to a network.      |
| `docker network disconnect [network name] [Container ID]` | Disconnect a container from a network. |

## Share

```{bash}
docker pull <image-name>
docker tag <source-image-name> <target-image-name>
```

## Examples

```{bash}
docker build -t <image-name>
docker image ls
docker image rm
```

```{sh}
docker container run --name cntnr -p 80:80 cntnr:cntnr
docker container stop cntnr
docker container kill cntnr
docker network ls
docker container ls
docker container rm -f $(docker ps -aq)
logs --tail 100 cntnr
```

```{bash}
docker run -i -t <container-name-or-id> bash
docker exec -it <container-name-or-id> bash
```

```{cmd}
docker ps

docker rm -f <container id>

docker rm -f $(docker ps -qa)

clear; docker rm -f $(docker ps -qa); .build.sh -w

docker logs apps_core?panel_1 --tail 100 -f
```
