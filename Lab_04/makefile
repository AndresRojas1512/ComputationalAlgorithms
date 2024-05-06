.PHONY : clean func unit release debug
CC := g++
CFLAGS := -std=c++20 -g3 -pedantic -Wextra -I/home/andres/BoostCpp/boost_1_85_0
LFLAGS := -L/home/andres/BoostCpp/boost_1_85_0/stage/lib -lboost_math_c99

INC := inc
OUT := out
SRC := src

SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp,$(OUT)/%.o, $(SRCS))

APP_EXE := app.exe

release: $(APP_EXE)

$(APP_EXE): $(OUT) | $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS) -lm

$(OUT)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@ -lm

$(OUT):
	mkdir -p $@

clean:
	rm -f -r $(OUT) *.exe
