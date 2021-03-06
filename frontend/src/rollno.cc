/**
 *       \file       rollno.cc
 *
 *       \brief      RollNo detail Class definition
 *
 *       \version    0.8
 *       \date       Sunday 07 April 2013 07:53:57  IST\n
 *       Compiler    g++
 *
 *       \author     Mandeep Kaur, meghasimak@gmail.com
 *       License     GNU General Public License
 *       \copyright  Copyright (c) 2013, GreatDevelopers
 *                   https://github.com/GreatDevelopers
 */

/**
 *  include rollno.h 
 */
#include "header/rollno.h"

/**
 *      \class  RollNoDetail
 *      \fn     RollNoDetail :: RollNoDetail()
 *      \brief  Constructor
 */

RollNoDetail :: RollNoDetail()
{
    // constructor
    totalCols = 6;
    tableHeading.resize(totalCols);

    i = 0;
    tableHeading[i++] = "Class Name";    
    tableHeading[i++] = "Subject Code";
    tableHeading[i++] = "Prefix";
    tableHeading[i++] = "Start Roll No.";
    tableHeading[i++] = "End Roll No.";
    tableHeading[i++] = "Not Included";
}

/**
 *      \class  RollNoDetail
 *      \fn     RollNoDetail :: ReadClassDetail()
 *      \brief  Reading class details from previous page and store
 *              them into database
 */

void RollNoDetail :: ReadClassDetail()
{

//    page.ContentType();

    projectID = readField.ReadFieldValue(fieldName.projectID);
    projectType = readField.ReadFieldValue(fieldName.projectType);
    totalClasses = StringToInt(readField.ReadFieldValue(
                               fieldName.totalClasses));
 
    rowIndex = readField.ReadFieldValue(fieldName.rowIndex);
    STRING_VEC index;
    SplitString(index, rowIndex, ",");

    className.resize(totalClasses);
    subjectName.resize(totalClasses);
    subjectCode.resize(totalClasses);
 
    for(i = 0; i < totalClasses; i++)
    {
        j = StringToInt(index[i]);
        className[i] = readField.ReadFieldValue(fieldName.className,
                                                j);

        subjectName[i] = readField.ReadFieldValue(
                         fieldName.subjectName, j);
        
        subjectCode[i] = readField.ReadFieldValue(
                         fieldName.subjectCode, j);
    }

    if(projectType == "Old")
    {
        where = "ProjectID = " + projectID;
        database.SelectColumn(prefix, "Prefix", "RollNoDetail", where);

        if(prefix.size() <= 0)
        {
            prefix.resize(totalClasses);
            startRollNo.resize(totalClasses);
            endRollNo.resize(totalClasses);
            notIncluded.resize(totalClasses);

//            SetDefaultValue(totalClasses);
            for(i = 0; i < totalClasses; i++)
            {
                prefix[i]       =   "";
                startRollNo[i]  =   "";
                endRollNo[i]    =   "";
                notIncluded[i]  =   "";
            }
        }
        else
        {
            database.SelectColumn(startRollNo, "StartRollNo", 
                                  "RollNoDetail", where);
            database.SelectColumn(endRollNo, "EndRollNo",
                                  "RollNoDetail", where);
            database.SelectColumn(notIncluded, "NotIncluded",
                                  "RollNoDetail", where);

            if(startRollNo.size() < unsigned(totalClasses))
            {
                j = startRollNo.size();
                prefix.resize(totalClasses);
                startRollNo.resize(totalClasses);
                endRollNo.resize(totalClasses);
                notIncluded.resize(totalClasses);

                for(i = j; i < totalClasses; i++)
                {
                    prefix[i]       =   "";
                    startRollNo[i]  =   "";
                    endRollNo[i]    =   "";
                    notIncluded[i]  =   "";
                }
            }
        }
        
            
    }
    else
    {
        SetDefaultValue(totalClasses);
    }
    WriteClassDetail();
}

/**
 *      \class  RollNoDetail
 *      \fn     RollNoDetail :: SetDefaultValue(int totalClasses)
 *      \brief  Setting default valued of i/p fields for taking i/p
 *              from user
 *      \param  totalClasses Total no. of rows/classes
 */

void RollNoDetail :: SetDefaultValue(int totalClasses)
{
    prefix.resize(totalClasses);
    startRollNo.resize(totalClasses);
    endRollNo.resize(totalClasses);
    notIncluded.resize(totalClasses);

    for(i = 0; i < totalClasses; i++)
    {
        prefix[i]       =   "Roll No Prefix";
        startRollNo[i]  =   "101";
        endRollNo[i]    =   "200";
        notIncluded[i]  =   "101-103, 190, 199";
    }
}

/**
 *      \class  RollNoDetail
 *      \fn     RollNoDetail :: WriteClassDetail()
 *      \brief  Write class details into database
 */

void RollNoDetail :: WriteClassDetail()
{
    where = "ProjectID = " + projectID;
    database.SelectColumn(vecTemp, "ClassName", "ClassDetail",
                          where);

    if(vecTemp.size() > 0 )
    {
        where = "ProjectID = " + projectID;
        database.DeleteQuery("ClassDetail", where);
    }

    for(i = 0; i < totalClasses; i++)
    {
        database.InsertClassDetail(projectID, className[i], 
                                   subjectName[i], subjectCode[i]);
    }
   
    /* Writing class details into I/P file*/
    subCode.resize(totalClasses);
    subName.resize(totalClasses);
    totalSubjects.resize(totalClasses);

    for(i = 0; i < totalClasses; i++)
    {
        SplitString(subCode[i], subjectCode[i], ",");
        
        SplitString(subName[i], subjectName[i], ",");
        
        totalSubjects[i] = subCode[i].size();
    }

    temp = FileName(CLASS_DETAIL, projectID, 1);
    outFile.open(temp.c_str());

    outFile << totalClasses << endl;
    for(i = 0; i < totalClasses; i++)
    {
        outFile << className[i] << endl
                << totalSubjects[i] << endl;
        for(j = 0; j < totalSubjects[i]; j++)
        {
            trim(subCode[i][j]);
            trim(subName[i][j]);
            outFile << subCode[i][j] << endl
                    << subName[i][j] << endl;
        }
    }

    outFile.close();
}

/**
 *      \class  RollNoDetail
 *      \fn     RollNoDetail :: RollNoDetailPage(string msg)
 *      \brief  RollNo detail page for taking i/p from user
 *      \param  msg For displaying error msg if any
 */

void RollNoDetail :: RollNoDetailPage(string msg)
{
    page.ContentType();

    ReadClassDetail();

    Header("Roll No Detail");

    cout << cgicc :: div().set("id", "DivRollNo");

//    page.LogoutLink();

//    cout << page.brk;

    cout << h1() << "Roll No Detail" << h1();// << page.brk;

    cout << form().set("id", "FormRollNo")
                  .set("action", "datesheet")
                  .set("method", "POST")
                  .set("onsubmit", 
                       "return ValidateRollNoForm('TotalClasses')");

    ErrorMessage(msg);

    page.InputField("hidden", fieldName.projectID, projectID);
    page.InputField("hidden", fieldName.totalClasses, 
                    IntToString(totalClasses));
    page.InputField("hidden", fieldName.projectType, projectType);

    cout << table().set("id", "TableRollNo");

    cout << tr();
    for(i = 0; i < totalCols; i++)
    {   
        cout << th() << tableHeading[i] << th();
    }
    cout << tr();

    for(i = 0; i < totalClasses; i++)
    {
        if(projectType == "Old")// && (prefix.size() > 1 || 
//           subjectName.size() >1 || subjectCode.size() > 1 ))
        {

            cout << tr();
        
            cout << td();
            cout << className[i];
            page.InputField("hidden", fieldName.className, (i + 1),
                            className[i]);
            cout << td();
       
            cout << td();
            cout << subjectCode[i];
            page.InputField("hidden", fieldName.subjectCode, (i + 1),
                            subjectCode[i]);
            cout << td();
        
            cout << td();
            page.InputField("text", fieldName.prefix, (i + 1),
                            prefix[i], prefix[i]);
            cout << td();
         
            cout << td();
            page.InputField("text", fieldName.startRollNo, (i + 1),
                            startRollNo[i], startRollNo[i]);
            cout << td();
         
            cout << td();
            page.InputField("text", fieldName.endRollNo, (i + 1),
                            endRollNo[i], endRollNo[i]);
            cout << td();
         
            cout << td();
            page.InputField("text", fieldName.notIncluded, (i + 1),
                            notIncluded[i], notIncluded[i]);
            cout << td();
 
            cout << tr();
        }
        else
        {
        
            cout << tr();
        
            cout << td();
            cout << className[i];
            page.InputField("hidden", fieldName.className, (i + 1),
                            className[i]);
            cout << td();
        
            cout << td();
            cout << subjectCode[i];
            page.InputField("hidden", fieldName.subjectCode, (i + 1),
                            subjectCode[i]);
            cout << td();
        
            cout << td();
            page.InputField("text", fieldName.prefix, (i + 1),
                            prefix[i]);
            cout << td();
         
            cout << td();
            page.InputField("text", fieldName.startRollNo, (i + 1),
                            startRollNo[i]);
            cout << td();
         
            cout << td();
            page.InputField("text", fieldName.endRollNo, (i + 1),
                            endRollNo[i]);
            cout << td();
         
            cout << td();
            page.InputField("text", fieldName.notIncluded, (i + 1),
                            notIncluded[i]);
            cout << td();
 
            cout << tr();
        }
    }
 
    cout << table();

    cout << br() << br();
    
    page.Button("next", "submit", "btn", "Next");

    cout << form() << cgicc :: div();

    Footer();
}

/**
 *      \class  RollNoDetail
 *      \fn     RollNoDetail :: ~RollNoDetail()
 *      \brief  Destructor
 */

RollNoDetail :: ~RollNoDetail()
{
    // destructor
}
