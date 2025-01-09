// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<defs.h>>

#ifndef DEFS_H
# define DEFS_H

# include <stdint.h>

// fixed width type aliases

typedef int8_t		i8;
typedef int16_t		i16;
typedef int32_t		i32;
typedef int64_t		i64;

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;

// frame structure

typedef struct frame	frame_t;

struct frame {
	u8	size;
	u8	*top;
	u8	*bot;
	u8	*lft;
	u8	*rgt;
};

// helper macros

# define alloc(x)	(ft_push(ft_alloc(x)))
# define inrange(x, y, z)	(x >= y && x <= z)

// error codes

# define E_INVALID_ARGC			1
# define E_NO_TERMINFO_FOUND	2
# define E_MISSING_TERMINFO_CAP	3
# define E_STDOUT_WRITE			4
# define E_ALLOC_FAIL			5
# define E_ARG_OUT_OF_RANGE		6
# define E_TOO_MANY_NUMBERS		7
# define E_NOT_ENOUGH_NUMBERS	8
# define E_TOO_MANY_LINES		9
# define E_NOT_ENOUGH_LINES		10
# define E_STDIN_READ			11
# define E_PIPE_FAIL			12
# define E_FORK_FAIL			13
# define E_EXEC_FAIL			14
# define E_DUP_FAIL				15
# define E_TIMESPEC_FAIL		16

// color codes

# ifndef COLOR_FRAME
#  define COLOR_FRAME 162
# endif

# ifndef COLOR_GRID
#  define COLOR_GRID 99
# endif

# ifndef COLOR_OK
#  define COLOR_OK 42
# endif

# ifndef COLOR_KO
#  define COLOR_KO 88
# endif

#endif
