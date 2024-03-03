.PHONY : clean func unit release debug
CC := g++
CFLAGS := -std=c++20 -Wall -Werror -pedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion

INC := inc
OUT := out
SRC := src


SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp,$(OUT)/%.o, $(SRCS))

APP_EXE := app.exe

release: $(APP_EXE)

$(APP_EXE): $(OUT) | $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lm

$(OUT)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@ -lm

$(OUT):
	mkdir -p $@

clean:
	rm -f -r $(OUT) *.exe
