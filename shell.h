#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define RB_SIZE 1024
#define WB_SIZE 1024
#define BUFSH -1
#define H_F	".shell_hist"
#define H_M	4096
#define NORM	0
#define OR		1
#define AND		2
#define CHAIN	3
#define USE_GETLINE 0
#define USE_STRTOK 0
#define CONV_LOW	1
#define CONV_UNSIGN	2




extern char **environ;


/**
 * struct lists - linked list
 * @n: int
 * @str: char
 * @next: lists
 */
typedef struct lists
{
	int n;
	char *str;
	struct lists *next;
} lists_t;

/**
 * struct psinf - list
 * @arg: car
 * @argv: car
 * @path: car
 * @argc: int
 * @lcount: int
 * @err_n: int
 * @lcount_f: int
 * @fn: car
 * @env: listt
 * @hist: listt
 * @alias: listt
 * @environ: car
 * @env_ch: int
 * @stat: int
 * @cmdb: car
 * @cmdb_type: int
 * @readfd: int
 * @hcount: int
 */
typedef struct psinf
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lcount;
	int err_n;
	int lcount_f;
	char *fn;
	lists_t *env;
	lists_t *hist;
	lists_t *alias;
	char **environ;
	int env_ch;
	int stat;

	char **cmdb;
	int cmdb_type;
	int readfd;
	int hcount;
} inf_o;

#define INF_IN \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - entry
 * @type: var
 * @func: var
 */
typedef struct builtin
{
	char *type;
	int (*func)(inf_o *);
} builtin_t;

/*get line*/
ssize_t buf_save(inf_o *inf, char **b, size_t *l);
ssize_t input_process(inf_o *);
int _getline(inf_o *, char **, size_t *);
void sigint_handler(int);

/*str tok*/
char **str_tok1(char *, char *);
char **str_tok2(char *, char);

int loophsh(char **);

/*env1 */
char *get_env_var(inf_o *, const char *);
int env_wrapper(inf_o *);
int set_env(inf_o *);
int unset_env(inf_o *);
int penv_list(inf_o *);

/*env2 */
char **get_env(inf_o *);
int unset_en_var(inf_o *, char *);
int set_up_en_var(inf_o *, char *, char *);

/*args */
void initialize_info(inf_o *);
void populate_info(inf_o *, char **);
void info_free(inf_o *, int);
int block_free(void **);

/*builtin1 */
int pnt_lnk_lst(inf_o *);
int mng_alias(inf_o *);

/*builtin2 */
int eexit(inf_o *);
int handle_cd(inf_o *);
int handle_help(inf_o *);

/*erprint1*/
int _str_to_int(char *);
void error_pnt(inf_o *, char *);
int int_pnt(int, int);
char *long_to_str(long int, int, int);
void comment_rm(char *);

/*erprint2*/
void _puts_error(char *);
int _put_error_char(char);
int _put_error_char_fd(char c, int f);
int _put_errors_fd(char *s, int f);

/*str*/
char *_str_cpy(char *, char *, int);
char *_str_n_cat(char *, char *, int);
char *_str_srch(char *, char);

/*history*/
char *hist_path(inf_o *inf);
int hist_file(inf_o *inf);
int read_hist_file(inf_o *inf);
int add_hist_file(inf_o *inf, char *b, int lc);
int as_hist_file(inf_o *inf);

/*mem*/
char *_mem_set(char *, char, unsigned int);
void free_mem(char **);
void *_realoc(void *, unsigned int, unsigned int);

/*var*/
int chained(inf_o *, char *, size_t *);
void mod_chain(inf_o *, char *, size_t *, size_t, size_t);
int cmd_aliasing(inf_o *);
int cmd_var_sub(inf_o *);
int replace_str(char **, char *);

/*list*/
lists_t *add_beg_list(lists_t **, const char *, int);
lists_t *add_end_ist(lists_t **, const char *, int);
size_t pstr_list(const lists_t *);
int node_delete(lists_t **, unsigned int);
void list_free(lists_t **);

/*list2*/
size_t len_lst(const lists_t *);
char **lst_to_str(lists_t *);
size_t pnt_list_struct(const lists_t *);
lists_t *prenode(lists_t *, char *, char);
ssize_t get_node(lists_t *, lists_t *);

/*args_per*/
int command_valid(inf_o *, char *);
char *get_substr(char *, int, int);
char *cmd_executable(inf_o *, char *, char *);

/*loop*/
int loop_ar(inf_o *, char **);
int _built_ins(inf_o *);
void n_built(inf_o *);
void cmd_fokr(inf_o *);

/*utils*/
int is_interactive(inf_o *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/*func1*/
char *_copy_string(char *, char *);
char *_duplicate_string(const char *);
void _puts(char *);
int _putchar(char);

/*func2*/
int _length_str(char *);
int _compare_str(char *, char *);
char *hay_need(const char *, const char *);
char *_app_str(char *, char *);

#endif /*SIMPLE_SHELL*/
