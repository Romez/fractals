koch:
	gcc -Wall -g -fsanitize=address koch.c -o main -lraylib -lm

snowflake_koch:
	gcc -Wall -g -fsanitize=address snowflake_koch.c -o main -lraylib -lm