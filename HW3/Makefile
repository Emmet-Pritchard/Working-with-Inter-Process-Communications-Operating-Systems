CC = gcc
OUT_EXE  = Starter
OUT_EXE1 = Fibb
OUT_EXE2 = Prime
OUT_EXE3 = Total
OUT_EXE4 = CharacterReader
FILES  = Starter.c
FILES1 = Fibb.c 
FILES2 = Prime.c 
FILES3 = Total.c
FILES4 = CharacterReader.c

build: fibb
	$(CC) -lrt -o $(OUT_EXE) $(FILES) -Wall 
fibb: prime
	$(CC) -lrt -o $(OUT_EXE1) $(FILES1) -Wall 
prime: total
	$(CC) -lrt -o $(OUT_EXE2) $(FILES2) -Wall 
total: characterReader
	$(CC) -lrt -o $(OUT_EXE3) $(FILES3) -Wall 
characterReader:
	$(CC) -o $(OUT_EXE4) $(FILES4) -Wall 
clean:
	rm -f $(OUT_EXE)
	rm -f $(OUT_EXE1)
	rm -f $(OUT_EXE2)
	rm -f $(OUT_EXE3)
	rm -f $(OUT_EXE4)
