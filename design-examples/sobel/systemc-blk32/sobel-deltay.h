// See LICENSE for license details.
/*[[[cog
     import cog
     from cog_acctempl import *
     from dut_params import dut
     if "thread_nm" not in globals():
       lst = cog.previous.lstrip('/').rstrip('\n').split('=')
       assert( lst[0]=="thread_nm")
       assert( len(lst)==2)
       global thread_nm
       thread_nm = lst[1]
     cog.outl( "//thread_nm=" + thread_nm)
  ]]]*/
//thread_nm=deltay
//[[[end]]] (checksum: 04a09a1951c5149f3f28f4d522d164af)

// Declare helper methods and class variables

/*[[[cog
     c = dut.get_cthread(thread_nm)
     cog.outl("void %s() {" % (c.nm,))
     for p in c.ports:
       cog.outl("  %s;" % p.reset)
  ]]]*/
void deltay() {
  mid0.reset_get();
  mid1.reset_put();
//[[[end]]] (checksum: 9119683738504161caa723b5f4a4a9a4)

  UInt16 ip = 0;
  UInt16 jc = 0;
  UInt16 jc_last;

  const unsigned int MAXBPR = 80;
  const unsigned int words_per_blk = 32;

  BlkMid d0[MAXBPR];
  BlkMid d1[MAXBPR];
  BlkMid d2[MAXBPR];
  BlkMid d3[MAXBPR];

  BlkMid cl;

  BlkMid d0_buf;
  BlkMid d1_buf;
  BlkMid d2_buf;
  BlkMid d3_buf;

  /*[[[cog
       if c.writes_to_done:
         cog.outl("done = false;")
    ]]]*/
  //[[[end]]] (checksum: d41d8cd98f00b204e9800998ecf8427e)
  wait();
  while (1) {
    if ( start) {

      UInt16 ni = config.read().get_num_of_rows();
      UInt16 bpr = config.read().get_row_size_in_blks();

      const unsigned int bi = 2;
      const short kl[2*bi+1][1] = { {1}, {4}, {6}, {4}, {1}};

      if ( ip == 0 && jc == 0) {
        jc_last = bpr-1;
      }

    /* this is an annoying thing to add for flow control */
      if ( ((ip != 0 && ip>=ni) || mid0.nb_can_get()) && (ip<bi || mid1.nb_can_put())) {

        if ( ip == 0 || ip < ni) {
          mid0.nb_get(cl);
        }
        if (ip >= ni) {
          mid1.nb_put(d0[jc]);
        } else if (ip >= bi) {
          BlkMid ocl;
          for( unsigned int k=0; k<words_per_blk; ++k) {
            ocl.data[k] = d0[jc].data[k] + cl.data[k] * kl[4][0];
          }
          mid1.nb_put( ocl);
        }
      
        /* ii=-1 */
        d0[jc_last] = d0_buf;
        for ( unsigned int k=0; k<words_per_blk; ++k) {
          d0_buf.data[k] = ((ip<ni) ? cl.data[k] * kl[3][0] : 0)
            + ((ip> 0) ? d1[jc].data[k]        : 0);
        }
        /* ii=0 */
        d1[jc_last] =  d1_buf;
        for ( unsigned int k=0; k<words_per_blk; ++k) {
          d1_buf.data[k] = ((ip<ni) ? cl.data[k] * kl[2][0] : 0)
            + ((ip> 0) ? d2[jc].data[k]        : 0);
        }
        /* ii=1 */
        d2[jc_last] =  d2_buf;
        for ( unsigned int k=0; k<words_per_blk; ++k) {
          d2_buf.data[k] = ((ip<ni) ? cl.data[k] * kl[1][0] : 0)
            + ((ip> 0) ? d3[jc].data[k]        : 0);
        }

        d3[jc_last] = d3_buf;
        for ( unsigned int k=0; k<words_per_blk; ++k) {
          d3_buf.data[k] = (ip<ni) ? cl.data[k] * kl[0][0] : 0;
        }

        jc_last = jc;

        ++jc;
        if ( jc == bpr) {
          ++ip;
          jc = 0;
          if ( ip == ni+bi) {
            ip = 0;
          }
        }
      }
    }
    wait();
  }
}
