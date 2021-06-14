#!/bin/bash

if [ "$(id -u)" -eq '0' ]; then
    USER_ID=${HOST_USER_ID}
    GROUP_ID=${HOST_GROUP_ID}
    USER_NAME=${HOST_USER_NAME}
    GROUP_NAME=${HOST_GROUP_NAME}

    groupadd -r -g ${GROUP_ID} ${GROUP_NAME}
    useradd -r -d /home/${GROUP_NAME} -s /bin/bash -u ${USER_ID} -g ${GROUP_NAME} -m ${USER_NAME}
    exec gosu ${USER_NAME} "$@"
fi
exec "$@"
