#!/bin/bash
if [ -d "/app/.git" ]; then
    cd /app
    git pull origin develop
else
    git clone -b develop https://github.com/Terps489/ISE_Lab1.git /app
fi
exec "$@"