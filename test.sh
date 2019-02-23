#!/bin/bash

gcc bdb.c -o db && docker-compose run tester rspec specs.rb