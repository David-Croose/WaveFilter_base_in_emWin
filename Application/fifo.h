/*****************************************************************************************

                              a simple fifo implementation.

*****************************************************************************************/

#ifndef _FIFO33_H_
#define _FIFO33_H_

#define ARR_CNT(x)    				(sizeof(x) / sizeof(x[0]))  /* array count */
#define F_TRUE    	(1)
#define F_FALSE		(!F_TRUE)

typedef double fdat_t;	/* you can configure the fdat_t to your need */
typedef enum {
	F_OK = 0,
	F_ERR_PA,		// parameter error
	F_ERR_NM,		// no memory
	F_ERR_BS,		// busy
} fres_t;			// fifo result

struct NODE {
	fdat_t *fifo;
	unsigned int head;
	unsigned int end;
	unsigned int fifo_deep;		/* this is fifo units total, not fifo size! */
	unsigned int lock_flag;
};

fres_t fifo_in(struct NODE *node, fdat_t *unit);
fres_t fifo_inl(struct NODE *node, fdat_t *unit);
fres_t fifo_out(struct NODE *node, fdat_t *unit);
fres_t fifo_read(struct NODE *node, fdat_t *units, unsigned int cnt, unsigned int *rc);
fres_t fifo_peep(struct NODE *node, fdat_t *units, unsigned int cnt, unsigned int *rc);
fres_t fifo_write(struct NODE *node, fdat_t *units, unsigned int cnt, unsigned int *wc);
fres_t fifo_writel(struct NODE *node, fdat_t *units, unsigned int cnt, unsigned int *wc);
fres_t fifo_init(struct NODE *node, fdat_t *fifo, unsigned int fifocnt);
fres_t fifo_deep(struct NODE *node, unsigned int *deep);
fres_t fifo_deeptotal(struct NODE *node, unsigned int *deeptotal);

#endif

