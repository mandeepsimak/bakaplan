#include "seatplan.h"

void SeatPlan :: readRoomDetails(string file)
{
    infile.open(file.c_str());
    infile >> total_centres;
//   getline(infile, centre_no[0], '\n');
    for(i = 0; i < total_centres; i++)
    {
       getline(infile, centre_no[i], '\n');
       getline(infile, centre_no[i], '\n');
       infile >> total_rooms[i];
//      getline(infile, room_no[i][0], '\n');
       for (j = 0; j < total_rooms[i]; j++)
       {
          getline(infile, room_no[i][j], '\n');
          getline(infile, room_no[i][j], '\n');
          infile >> rows[i][j] >> cols[i][j];
       }
    }
    infile.close();
}

void SeatPlan :: readSubjectWiseRollNo(string file)
{
    infile.open(file.c_str());
    infile >> total_code;
    //getline(infile, sub_subcode[0], '\n');
    for(i = 0; i < total_code; i++)
    {
        getline(infile, sub_subcode[i], '\n');
        getline(infile, sub_subcode[i], '\n');
        infile >> sub_totalrno[i];
       
        for(j = 0; j < sub_totalrno[i]; j++)
            infile >> sub_rollno[i][j];
    }
    infile.close();
}

void SeatPlan :: setRollNo(int strategy)
{
    s = 0;
    for(i = 0; i < strategy; i++)
    {
        seat_size[i] = 0;
    }
    
    for(i = 0; i < total_code; i++)
    {
        if(s == strategy)
            s = 0;
        
        start = seat_size[s];
        index = index_value[i];
        end = sub_totalrno[index];
        
        for(j = 0; j < end; j++)
        {
            seat_rollno[s][start + j] = sub_rollno[index][j];
        }
        
        seat_size[s] = start + end;
        s++;
    }    
}

void SeatPlan :: seatingPlan(int strategy)
{
    setRollNo(strategy);
    
    for(i = 0; i < strategy; i++)
    {
        size[i] = 0;
    }
    
    // centre = total centre, room = total room[], row = rows[][], col = cols[][]
    
    for(centre = 0; centre < total_centres; centre++)
    {
        for(room = 0; room < total_rooms[centre]; room++)
        {
            for(row = 0; row < cols[centre][room]; row++)
            {
                if((row % 2) != 0)
                {
                    if(strategy == 2)
                        s = 1;
                    if(strategy > 2)
                        s = 2;
                }
                else
                    s = 0;
          
                for(col = 0; col < rows[centre][room]; col++)
                {
                    if(s == strategy)
                        s = 0;
                    seat[centre][room][col][row] = rollNo(s);
                    s++;
                }
            }
        }
    }
}


string SeatPlan :: rollNo(int s)
{
    string rno;
    
    if(seat_size[s] == size[s])
        rno = "  ";
    else
    {
        rno = seat_rollno[s][size[s]];
        size[s]++;
    }
    return rno;
}

void SeatPlan :: showSeatPlan()
{
    outfile.open(SeatPlan_out);
    outfile << total_centres << endl;
    for(centre = 0; centre < total_centres; centre++)
    {
        outfile << centre_no[centre] << endl
                << total_rooms[centre] << endl;
        for(room = 0; room < total_rooms[centre]; room++)
        {
            outfile << room_no[centre][room] << endl;
            for(row = 0; row < rows[centre][room]; row++)
            {
                for(col = 0; col < cols[centre][room]; col++)
                {
                    outfile << seat[centre][room][row][col] << "\t";
                }
                outfile << "\n";
            }
        }
    }
    outfile.close();
    
    infile.open(Input_ExamDetails);
    getline(infile, exam_name, '\n');
    getline(infile, exam_date, '\n');
    getline(infile, exam_time, '\n');
    getline(infile, exam_venue, '\n');
    infile.close();
    
    outfile.open(SeatPlan_HTMLFile);
    outfile << "<html><head><title>BaKa Plan</title>"
            << "<style> @media print { div {page-break-before:always} } </style> </head>"
            << "<body align = \"center\" > <pre>"
            //<< "<br><br> " //<h2> Seating Plan </h2> <br>";//" <b> Total Centres: "
            
            << endl;
//            << total_centres << "</b> " << endl;
    for(centre = 0; centre < total_centres; centre++)
    {
                
        for(room = 0; room < total_rooms[centre]; room++)
        {
            outfile << "<h3>"
                    << "Examination :   " << exam_name << "<br>"
                    << "Date : " << exam_date << "<br>"
                    << "Time : " << exam_time << "<br>"
                    << "Venue : " << exam_venue << "<br>"
                    << "</h3>";
            
            outfile << "<b><br> Centre Name: </b>" << centre_no[centre] << endl;
//                <<  "<b>     Total Rooms: </b>" << total_rooms[centre] 
            outfile << "<br><b>Room No: </b>" << room_no[centre][room] << endl << "<br>"
                    << "<table align = \"center\" cellpadding = \"8\""
                    << " cellspacing = \"1\" border = \"1\">";
            outfile << "<tr>";
                j = 65 + cols[centre][room];
                for(i = 64; i < j; i++)
                {
                    char a;
                    if (i==64)
                        a = ' ';
                    else
                        a = i;
                    outfile << "<th width = \"80\" height = \"30\""
                            << " align = \"center\" valign = \"center\">" 
                            << a << "</th>";
                }
                outfile << "</tr>";
            for(row = 0; row < rows[centre][room]; row++)
            {
                
                outfile << "<tr><td width = \"80\" height = \"30\" "
                        << "align = \"center\" valign = \"center\">"
                        << row+1
                        << "</td>";
                for(col = 0; col < cols[centre][room]; col++)
                {
                    outfile << "<td width = \"80\" height = \"30\" "
                            << "align = \"center\" valign = \"center\">" 
                            << seat[centre][room][row][col] 
                            << "</td>";
                }
                outfile << "</tr>";
            }
            outfile << "</table>";
            outfile << "<div>  </div>";
        }
    }
    outfile.close();
    
}
