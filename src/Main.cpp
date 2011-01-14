/*
 * Title: 主函数
 * Description: 主函数
 * Copyright (c) 2010 Nano.Studio, All rights reserved.
 * 
 * Version : 1.0
 *
 * Create    
 *     Author: Dalton
 *     Date: 2011-01-02
 *     Email: zhust2003@gmail.com 
 */

#include "World.h"
#include "ByteBuffer.h"
#include "utils/Config.h"
#include "ace/CDR_Stream.h"
#include "ace/Basic_Types.h"
#include "WorldTask.h"
#include "utils/Logger.h"
#include <vector>

/**
 * @brief   ACE_TMAIN 
 *
 * @param   argc
 * @param   argv
 *
 * @return  
 */
int ACE_TMAIN(int argc, ACE_TCHAR **argv) {    
    gLogger->info("<============================================================================>\n");
    gLogger->info(" )HQQQQc      :HQQQ8[        ]QQ(      9WQQQm       3$QQWH`     <yQ@T?VQQw.   \n");
    gLogger->info("   -$QQm        :Qf         .QQQ[        )QQQc        3Q`     .yQ@'    'WWm,  \n");
    gLogger->info("    ]WQQL       :Q(         jQQQf         QQQQ.       jD     _mQ@`      )WQm  \n");
    gLogger->info("    jWQQQ,      <Q`        _W]QQk        .QQWQL       df     mQQ'        $WQr \n");
    gLogger->info("    d[$QQL      ]@         mf=QQm        <W)WQQ,      Q[    jQQE         jQQk \n");
    gLogger->info("    Q')WQQ/     jk        ]@ -QQQ        ]E 4QQk     .Q'   .QWQ[         ]QQW \n");
    gLogger->info("   :Q` 4QQm     mf       .Q(  QQQ;       jf +QQQc    ]W    ]QQQ`         ]QQQ \n");
    gLogger->info("   ]@  -QQQc    Q(       jP   $QQ>       m[  4QQm    ]E    jQQ@          jQQQ \n");
    gLogger->info("   jk   ]QQQ.  :Q`      _Q'   3QQ[      .Q'  -QWQL   jf    mQQk          jQQD \n");
    gLogger->info("   df   -QQQL  ]@       mmwaawdQQL      =Q    ]QQQ,  m[    QQQf          mQQf \n");
    gLogger->info("   Q[    ]WQQ, jF      ]W?????4QQk      ]B     $QQL .Q'    QQQf         .QQQ( \n");
    gLogger->info("  :Q`     $WQk d[     .Q[     )QQm      jk     )QQQ/=W     QWQf         ]QQ@  \n");
    gLogger->info("  ]W      +WQQcQ'     j@      :QQQ      mf      4QQm]E     3QQL         mQQ(  \n");
    gLogger->info("  jE       4QQmW     _Q(       QQQ;    .Q(      -QQQQf     ]QQm        <QQF   \n");
    gLogger->info("  df       -QQQ@     dE        QQQ(    =Q`       4QQW[      WQQ/      _QQP    \n");
    gLogger->info(" .Qk        ]QQk    jW[        mQQL    jQ;        QWQ;      +QWm,    _QW?     \n");
    gLogger->info("mQQQmz       $Qf  =mWQQmr    qQQQQQQc]mQQQm;      ]WQ        -9QQgwwmWP'      \n");
    gLogger->info("<================================Version 0.1=================================>\n");

    gConfig->open("nano.ini");
    
    // 启动世界进程
    WorldTask wt;
    wt.activate();
    
    gWorld->init();
//    gWorld->run();
	return 0;
}
