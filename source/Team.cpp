#include "Team.h"

// Prints a given character in the color coresponding to the team it refers.
void print_colored_string(const char ch, const Team team)
{
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // used for coloring output text
      if( team != Team::Neutral ) // if the string refers to a team
      {
            uint8_t color = WHITE_COLOR;     
            switch (team)
            {
                  case Team::Neutral : color = WHITE_COLOR; break; // not used but written for programming purposes
                  case Team::Red     : color = 12; break;
                  case Team::Blue    : color =  9; break;
                  case Team::Tan     : color =  6; break;
                  case Team::Green   : color = 10; break;
                  case Team::Orange  : color =  8; break;
                  case Team::Purple  : color =  5; break;
                  case Team::Teal    : color = 11; break;
                  case Team::Pink    : color = 13; break;
            }
            SetConsoleTextAttribute(hConsole, color);
      }
      else
            SetConsoleTextAttribute(hConsole, WHITE_COLOR);

      printf("%c", ch);
      SetConsoleTextAttribute(hConsole, WHITE_COLOR); // to make sure the rest of the text is in white
}

// Prints a given string in the color coresponding to the team it refers.
void print_colored_string(const std::string str, const Team team)
{
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // used for coloring output text
      if( team != Team::Neutral ) // if the string refers to a team
      {
            uint8_t color = WHITE_COLOR;     
            switch (team)
            {
                  case Team::Neutral : color = WHITE_COLOR; break; // not used but written for programming purposes
                  case Team::Red     : color = 12; break;
                  case Team::Blue    : color =  9; break;
                  case Team::Tan     : color =  6; break;
                  case Team::Green   : color = 10; break;
                  case Team::Orange  : color =  8; break;
                  case Team::Purple  : color =  5; break;
                  case Team::Teal    : color = 11; break;
                  case Team::Pink    : color = 13; break;
            }
            SetConsoleTextAttribute(hConsole, color);
      }
      else
            SetConsoleTextAttribute(hConsole, WHITE_COLOR);

      printf("%s", str.c_str());
      SetConsoleTextAttribute(hConsole, WHITE_COLOR); // to make sure the rest of the text is in white
}