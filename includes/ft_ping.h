#ifndef FT_PING_H
# define FT_PING_H

# include <arpa/inet.h>
# include <float.h>
# include <errno.h>
# include <limits.h>
# include <netdb.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SEND_DELAY			1
# define ADDR_SIZE			64
# define PAYLOAD_SIZE		56
# define MSG_CONTROL_SIZE	64

# define NB_OPTIONS			6
# define NB_IPV4_OPTIONS	0

# define ERR_NO_ARGS		0
# define ERR_NB_DEST		1
# define ERR_INV_OPT		2
# define ERR_INV_ARG		3
# define ERR_OOR_ARG		4 /* OUT OF RANGE */
# define ERR_REQ_ARG		5

/*
	Documentation: 
	https://en.wikipedia.org/wiki/Ping_(networking_utility)
	https://en.wikipedia.org/wiki/IPv4#Header
	https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol
*/

typedef struct		s_icmp_packet
{
	struct iphdr	iphdr; // 20 bytes
	struct icmphdr	icmphdr; // 8 bytes
	char			payload[PAYLOAD_SIZE]; // sizeof(struct timeval) + 40 bytes = 56 bytes
}					t_icmp_packet; // 84 bytes in ipv4 (not a norm tho)

typedef struct		s_timer
{
	double			min;
	double			max;
	double			sum;
	long long		tsum;
	long long		tsum2;
}					t_timer;

typedef struct		s_stats
{
	uint16_t		transmitted;
	uint16_t		received;
	uint16_t		errors;
	t_timer			timer;
	struct timeval	start;
	struct timeval	end;
}					t_stats;

typedef struct		s_options
{
	int				f;
	int				t;
	int				v;
	int				w;
}					t_options;

typedef struct		s_ping
{
	char				*prg_name;
	char				*hostname;
	char				address[ADDR_SIZE];
	uint32_t			ip_addr;
	struct sockaddr_in	sockaddr;
	int					sockfd;
	int					ttl_val;
	int					time_max;
	t_stats				stats;
	t_options			options;
}					t_ping;

extern t_ping		g_ping;

/* send_packet.c */
void	send_packet(int signum);

/* recv_packet.c */
void	recv_packet(void);

/* ping_stats.c */
void	ping_stats(int signum);

/* args.c */
int			check_args(int argc, char *argv[], t_ping *ping);

/* error.c */
int			getaddrinfo_error(int error, char *str);
void		print_help_menu(void);
int			args_error(int error, char *str, int range1, int range2);

/* utils.c */
double		get_diff_ms(struct timeval *start, struct timeval *end);
long		ft_sqrt(long long nb, long long x);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
int			is_num(const char *str);
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);

#endif
