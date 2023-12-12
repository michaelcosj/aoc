{$MODE DELPHI}

Program Hello;

Uses SysUtils, StrUtils, Math;

Const 
  TestInput: ansiString = 'Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53' + LineEnding +
                          'Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19' + LineEnding +
                          'Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1' + LineEnding +
                          'Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83' + LineEnding +
                          'Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36' + LineEnding +
                          'Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11';

Var 
  inputFile: text;


Function ArrayIncludes (arr: TStringArray; element: String): boolean;

Var 
  arrEl: string;
Begin
  For arrEl In arr Do
    If (CompareStr(arrEl, element) = 0) And (arrEl <> ' ') Then
      Begin
        ArrayIncludes := true;
        break;
      End
End;


Procedure PrintArray (arr: TStringArray);

Var 
  arrEl: string;
Begin
  For arrEl In arr Do
    write(arrEl, ', ');
  writeln('');
End;

Function PartOne (): longint;

Var 
  inputFile: text;
  currLine: string;

  card: TStringArray;
  lists: TStringArray;

  winNumbers: TStringArray;
  ownNumbers: TStringArray;

  num: string;
  points: integer;
  res: longint = 0;
Begin
  assign(inputFile, './input');
  reset(inputFile);

  While Not Eof(inputFile) Do
    Begin
      ReadLn(inputFile, currLine);
      If IsEmptyStr(Trim(currLine), [' ' , LineEnding]) Then
        continue;

      card := SplitString(currLine, ':');
      lists := SplitString(card[1], '|');

      winNumbers := SplitString(Trim(lists[0]), '  ');
      winNumbers := SplitString(String.join(' ', winNumbers), ' ');

      ownNumbers := SplitString(Trim(lists[1]), '  ');
      ownNumbers := SplitString(String.join(' ', ownNumbers), ' ');

      points := 0;
      For num In winNumbers Do
        If ArrayIncludes(ownNumbers, num) Then
          points := points + 1;
      res := res + trunc(IntPower(2, points - 1));
    End;

  PartOne := res;
End;



Begin
  writeln('Part One = ', PartOne());
End.
