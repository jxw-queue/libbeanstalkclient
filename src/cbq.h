/**
 * =====================================================================================
 * @file     cbq.h
 * @brief    header file for 
 * @date     08/15/2010 08:44:30 PM
 * @author   Roey Berman, (roey.berman@gmail.com)
 * @version  1.0
 *
 * Copyright (c) 2010, Roey Berman, (roeyb.berman@gmail.com)
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by Roey Berman.
 * 4. Neither the name of Roey Berman nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY ROEY BERMAN ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROEY BERMAN BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * =====================================================================================
 */

#ifndef CBQ_H
#define CBQ_H 

#ifdef __cplusplus
    extern "C" {
#endif

#include <arrayqueue.h>
#include "beanstalkclient.h"

struct _cbq_node;
union  bsc_cmd_info;

typedef void (*bsc_cb_p_t)(struct _bsc *, struct _cbq_node *, const char *, size_t);

struct _cbq_node {
    void  *data;
    int    len;
    bool   is_allocated;
    size_t bytes_expected;
    off_t  outq_offset;
    union  bsc_cmd_info *cb_data;
    bsc_cb_p_t cb;
};

AQ_DEFINE_STRUCT(_cbq, struct _cbq_node);

typedef struct _cbq_node cbq_node;
typedef struct _cbq      cbq;

#define CBQ_ENQ_FIN(c) (AQ_ENQ_FIN((c)->cbqueue), (c)->buffer_fill_cb != NULL ? (c)->buffer_fill_cb(c) : 0)

#define CBQ_DEQ_FIN(q) do {        \
    if (AQ_REAR_(q)->is_allocated) \
        free(AQ_REAR_(q)->data);   \
    AQ_DEQ_FIN(q);                 \
} while (false)

cbq *cbq_new(size_t size);

#ifdef __cplusplus
    }
#endif

#endif /* CBQ_H */
