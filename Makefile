TARGET = zexsh
OBJ = main.c input_parser.c helpers.c builtins.c
CC = gcc

all :	
	$(CC) -o $(TARGET) $(OBJ)
clean : 
	rm -f $(TARGET) *.o
fclean : clean
	rm -f $(TARGET)
re : fclean all
 