/**
 *       \file       validation.h
 *
 *       \brief      ValidStrategy class
 *
 *       \version    0.7
 *       \date       Sunday 07 April 2013 08:24:00  IST\n
 *       Compiler    g++
 *
 *       \author     Mandeep Kaur, meghasimak@gmail.com
 *       License     GNU General Public License
 *       \copyright  Copyright (c) 2013, GreatDevelopers
 *                   https://github.com/GreatDevelopers
 */

#ifndef VALIDATION_H
#define VALIDATION_H

/**
 *  include inpudetail.h 
 */
#include "inputdetail.h"
#include "../backend/header/strategy.h"

class ValidStrategy : public InputDetail
{
    protected:

    Strategy validStrategy;

    STRING_VEC selectedStrategy, totalSeats, totalGroupSeats, 
               totalStudents, totalGroupStudents;
    STRING_VEC valid;

    public:
        /** Constructor */
        ValidStrategy();

        /** Read Strategy Detail */
        void ReadStrategyDetail();

        /** Write Strategy Detail */
        void WriteStrategyDetail();

        /** Read ValidStrategy.out file */
        void ReadValidStrategy();

        /** ValidStrategy Page */
        void ValidStrategyPage();
    
        /** desrtuctor  */
        ~ValidStrategy();
};

#endif