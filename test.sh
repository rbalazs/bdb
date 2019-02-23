#!/bin/bash

gcc -std=c99 bdb.c -o db && docker-compose run tester rspec specs.rb