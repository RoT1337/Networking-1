#!/bin/bash

gcc -o Server Server.c -lws2_32
gcc -o Client Client.c -lws2_32