HEADER	=	Colors.hpp \
			IteratorsTraits.hpp \
			LexicographicalCompare.hpp \
			map.hpp \
			pair.hpp \
			RandomAccessIterator.hpp \
			RbIterator.hpp \
			RbNode.hpp \
			RbReverseIterator.hpp \
			RedBlackTree.hpp \
			RemoveConst.hpp \
			ReverseIterator.hpp \
			stack.hpp \
			Utility.hpp \
			vector.hpp \
			set.hpp

NAME	=	a.out
NAME_M	=	m.out
NAME_V	=	v.out
NAME_S	=	s.out
NAME_SET	=	set.out

SRCS	=	main.cpp
SRCS_M	=	check_map.cpp
SRCS_V	=	check_vector.cpp
SRCS_S	=	check_stack.cpp
SRCS_SET	=	check_set.cpp

OBJS	=	${SRCS:.cpp=.o}
OBJS_M	=	${SRCS_M:.cpp=.o}
OBJS_V	=	${SRCS_V:.cpp=.o}
OBJS_S	=	${SRCS_S:.cpp=.o}
OBJS_SET	=	${SRCS_SET:.cpp=.o}
C		=	c++

R		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror 

C98	= -std=c++98

%.o: %.cpp	${HEADER} ${SRS} ${SRCS_S} ${SRCS_M} ${SRCS_V}
	$(C) $(CFLAGS) ${C98} -I. -c $< -o ${<:.cpp=.o}

all:	$(NAME)

map :${OBJS_M} ${HEADER}
	${C} ${CFLAGS} ${C98} ${OBJS_M} -o $(NAME_M)

vector :${OBJS_V} ${HEADER}
	${C} ${CFLAGS} ${C98} ${OBJS_V} -o $(NAME_V)

stack :${OBJS_S} ${HEADER}
	${C} ${CFLAGS} ${C98} ${OBJS_S} -o $(NAME_S)

set :${OBJS_SET} ${HEADER}
	${C} ${CFLAGS} ${C98} ${OBJS_SET} -o $(NAME_SET)

$(NAME): ${OBJS} ${HEADER}
	${C} ${CFLAGS} ${C98} ${OBJS} -o $(NAME)

clean:
	${R} $(OBJS)
	${R} $(OBJS_M)
	${R} $(OBJS_V)
	${R} $(OBJS_S)
	${R} $(OBJS_SET)

fclean:		clean
	${R} $(NAME)
	${R} $(NAME_M)
	${R} $(NAME_V)
	${R} $(NAME_S)
	${R} $(NAME_SET)
	
re:			clean all


.PHONY:		all clean fclean re
