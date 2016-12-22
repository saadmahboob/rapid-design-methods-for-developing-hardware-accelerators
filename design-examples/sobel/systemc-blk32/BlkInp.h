// See LICENSE for license details.

/*[[[cog
     import cog
     from cog_acctempl import *
     from dut_params import *
     if "ty" not in globals():
       lst = cog.previous.lstrip('/').rstrip('\n').split('=')
       assert( lst[0]=="ty")
       assert( len(lst)==2)
       global ty
       ty = lst[1]
     cog.outl( "//ty=" + ty)
     ut = dut.usertypes[ty]
  ]]]*/
//ty=BlkInp
//[[[end]]] (checksum: d575e88ea9bf928303e8ca26fc27bd15)
/*[[[cog
     cog.outl("#ifndef %s_H_" % ty)
     cog.outl("#define %s_H_" % ty)
  ]]]*/
#ifndef BlkInp_H_
#define BlkInp_H_
//[[[end]]] (checksum: 3b64b6ca86061935b3b5d9f9e8fdb3da)

#ifndef __SYNTHESIS__
#include <cstddef>
#include <cassert>
#endif

/*[[[cog
     cog.outl("class %s {" % ty)
  ]]]*/
class BlkInp {
//[[[end]]] (checksum: c91fbfe9dc51537311ee1fc56686c6c2)
public:
  /*[[[cog
       for field in ut.fields:
         cog.outl( field.declaration)
    ]]]*/
  unsigned char data[32];
  //[[[end]]] (checksum: d98f9885fd7d30f72320e1504deffef4)

  /*[[[cog
       cog.outl("enum { BitCnt = %d };" % ut.bitwidth)
    ]]]*/
  enum { BitCnt = 256 };
  //[[[end]]] (checksum: a641fbc923747c10e4cf6e3f11569112)

  static size_t getBitCnt() {
    /*[[[cog
         cog.outl("assert(sizeof(%s) == (size_t) BitCnt/8);" % ty)
      ]]]*/
    assert(sizeof(BlkInp) == (size_t) BitCnt/8);
    //[[[end]]] (checksum: 7dc98c72ce6be47337bfa5042d0348e1)
    assert( 0 == (size_t) BitCnt%8);
    return BitCnt;
  }
  static size_t numberOfFields() {
    /*[[[cog
         cog.outl("return %d;" % ut.numberOfFields)
      ]]]*/
    return 32;
    //[[[end]]] (checksum: 163e9ad09a380163fbc65c841051d031)
  }
  static size_t fieldWidth( size_t index) {
    /*[[[cog
         sum = 0
         for field in ut.fields:
            cog.outl("if ( %d <= index && index < %d) {" % (sum,sum+field.numberOfFields))
            cog.outl( field.fieldWidth( sum))
            cog.outl("}")
            sum += field.numberOfFields
      ]]]*/
    if ( 0 <= index && index < 32) {
      return 8;
    }
    //[[[end]]] (checksum: c8c6aa6074ee6cb6c86f9a0f544e8d9b)
    return 0;
  }
  void putField(size_t index, UInt64 d) {
    /*[[[cog
         sum = 0
         for field in ut.fields:
            cog.outl("if ( %d <= index && index < %d) {" % (sum,sum+field.numberOfFields))
            cog.outl( field.putField( sum))
            cog.outl("}")
            sum += field.numberOfFields
      ]]]*/
    if ( 0 <= index && index < 32) {
      data[index-0] = d;
    }
    //[[[end]]] (checksum: 9d402e9f650ebc0f2f5eb923ecab8c0a)
  }
  UInt64 getField(size_t index) const {
    /*[[[cog
         sum = 0
         for field in ut.fields:
            cog.outl("if ( %d <= index && index < %d) {" % (sum,sum+field.numberOfFields))
            cog.outl( field.getField( sum))
            cog.outl("}")
            sum += field.numberOfFields
      ]]]*/
    if ( 0 <= index && index < 32) {
      return data[index-0];
    }
    //[[[end]]] (checksum: bebe841769a6348fc48a3a8dd54f6f27)
    return 0;
  }

#if !defined(__AAL_USER__) && !defined(USE_SOFTWARE)
  /*[[[cog
       cog.outl("inline friend void sc_trace(sc_trace_file* tf, const %s& d, const std::string& name) {" % ty)
    ]]]*/
  inline friend void sc_trace(sc_trace_file* tf, const BlkInp& d, const std::string& name) {
  //[[[end]]] (checksum: b51b512527feda4293871d8aa0ddc229)
  }
#endif

  /*[[[cog
       cog.outl("inline friend std::ostream& operator<<(std::ostream& os, const %s& d) {" % ty)
       cog.outl("  os << \"<%s>\";" % ty)
    ]]]*/
  inline friend std::ostream& operator<<(std::ostream& os, const BlkInp& d) {
    os << "<BlkInp>";
  //[[[end]]] (checksum: 2520da46de25202ded8ed23df2b635ad)
    return os;
  }

  /*[[[cog
       cog.outl("inline bool operator==(const %s& rhs) const {" % ty)
    ]]]*/
  inline bool operator==(const BlkInp& rhs) const {
  //[[[end]]] (checksum: 70031a6e19291be0a66ac22cf7b3bcc8)
    bool result = true;
    for( unsigned int i=0; i<numberOfFields(); ++i) {
      result = result && (getField(i) == rhs.getField(i));
    }
    return result;
  }

};

#endif
