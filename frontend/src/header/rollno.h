/**
 *       \file       rollno.h
 *
 *       \brief      RollNo class declaration for taking roll no
 *                   detail
 *
 *       \version    0.7
 *       \date       Sunday 07 April 2013 07:51:45  IST\n
 *       Compiler    g++
 *
 *       \author     Mandeep Kaur, meghasimak@gmail.com
 *       License     GNU General Public License
 *       \copyright  Copyright (c) 2013, GreatDevelopers
 *                   https://github.com/GreatDevelopers
 */

#ifndef ROLLNO_H
#define ROLLNO_H

/**
 *  include class.h 
 */

#include "inputdetail.h"


/**
 *      \class  RollNoDetail
 *      \brief  RollNoDetail class for taking roll no detail from user
 */

class RollNoDetail : public InputDetail
{
    protected:

    public:
        /** Roll No detail Constructor*/
        RollNoDetail();

        /** Read Class Details */
        void ReadClassDetail();

        /** Write class details in database */
        void WriteClassDetail();

        /** Set default values of field */
        void SetDefaultValue(int totalClasses);

        /** RollNo detail page */
        void RollNoDetailPage(string msg="");

        /** Destructor */
        ~RollNoDetail();
};

#endif