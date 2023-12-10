-- ***********************
-- Name: Wilson Sum, Gordon Tan 
-- ID: 017142142, 147206221
-- Group #13 
-- Date: The current date
-- Purpose: Assignment 2 - DBS311
-- Section: NEE
-- ***********************

SET SERVEROUTPUT ON;
/*
1.	For each table in (Players, Teams, Rosters) create Stored Procedures to cover the 4 basic CRUD tasks.
a.	INSERT a new record and if the PK using autonumber, the SP returns the new PK,
b.	UPDATE an existing record given the PK value,
c.	DELETE an existing record given the PK value, and
d.	SELECT return all fields in a single row from a table given a PK value.

•	Name the SPs using the following guide:  spTableNameMethod (example spPlayersInsert)
•	Do not use DBMS_OUTPUT in the procedures in any way.  If you use it for debugging purposes, make sure it is commented out in the final submission.
•	All SPs must have appropriate exception handling specific to the method and table.
•	Use error codes of the same type and size of the PK to return values that can be clearly determined to 
    indicate an error (example: -1 might indicate no record was found). These should be consistent values across all 
    SPs such that only a single table of error codes is required in the documentation.
*/
CREATE OR REPLACE PROCEDURE spPlayersInsert(
    id players.playerid%TYPE,
    num players.regnumber%TYPE,
    lname players.lastname%TYPE,
    fname players.firstname%TYPE,
    active players.isactive%TYPE,
    errorCode OUT INT
)AS
BEGIN
    INSERT INTO players(playerid, regnumber, lastname, firstname, isactive)
    VALUES( id, num, lname, fname, active);
    errorCode:=1;
EXCEPTION 
    WHEN DUP_VAL_ON_INDEX
        THEN errorCode:=-2;
    WHEN OTHERS
        THEN errorCode := -3;
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spPlayersInsert(101, 10, 'Bob', 'Tesla', 1, errorCode);
    spPlayersInsert(101, 10, 'Bob', 'Tesla', 1, errorCode);
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spPlayersInsert(105, 10, 'Terra', 'Tesla', 1, errorCode);
END;

CREATE OR REPLACE PROCEDURE spPlayersUpdate(
    id players.playerid%TYPE,
    num players.regnumber%TYPE,
    lname players.lastname%TYPE,
    fname players.firstname%TYPE,
    active players.isactive%TYPE,
    errorCode OUT INT
)AS
    rowCount INT;
BEGIN
    UPDATE players
    SET 
        playerid = id,
        regnumber = num,
        lastname = lname,
        firstname = fname,
        isactive = active
    WHERE playerid = id;
    
    errorCode:=1;
    rowCount := SQL%ROWCOUNT;
    
    IF rowCount = 0 THEN
        errorCode := -1;
    END IF;

EXCEPTION 
    WHEN OTHERS
        THEN errorCode := -3;
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spPlayersUpdate(600, 10, 'Bob', 'Tesla', 1, errorCode);
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spPlayersUpdate(1303, 10, 'Bob', 'Tesla', 1, errorCode);
END;

CREATE OR REPLACE PROCEDURE spPlayersDelete(
    id players.playerid%TYPE,
    errorCode OUT INT
)AS
    rowC INT;
BEGIN
    DELETE players
    WHERE playerid = id;
    errorCode:=1;

    rowC :=SQL%ROWCOUNT;
    IF rowC = 0 THEN
        errorCode := -1;
    END IF;
    
EXCEPTION 
    WHEN OTHERS 
        THEN errorCode:=-3;
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spPlayersDelete(600, errorCode);
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spPlayersDelete(1304, errorCode);
END;

CREATE OR REPLACE PROCEDURE spPlayersSelect(
    id players.playerid%TYPE,
    pRow OUT players%ROWTYPE,
    errorCode OUT INT
)AS
BEGIN
    SELECT 
        playerid, 
        regnumber, 
        lastname, 
        firstname, 
        isactive
    INTO pRow
    FROM players
    WHERE playerid = id;
    errorCode:=1;
EXCEPTION 
    WHEN NO_DATA_FOUND
        THEN errorCode:=-1;
    WHEN OTHERS 
        THEN errorCode := -3;
END;

DECLARE
    err INT:=0;
    pRow players%ROWTYPE;
BEGIN
    spPlayersSelect(1302,pRow,err);
END;

DECLARE
    err INT:=0;
     pRow players%ROWTYPE;
BEGIN
    spPlayersSelect(600,pRow,err);
END;


CREATE OR REPLACE PROCEDURE spTeamsInsert(
    id teams.teamid%TYPE,
    name teams.teamname%TYPE,
    active teams.isactive%TYPE,
    colour teams.jerseycolour%TYPE,
    errorCode OUT INT
)AS
BEGIN
    INSERT INTO teams(teamid, teamname, isactive, jerseycolour)
    VALUES(id, name, active, colour);
    errorCode :=1;
    
EXCEPTION 
    WHEN DUP_VAL_ON_INDEX
        THEN errorCode:=-2;
    WHEN OTHERS
        THEN errorCode := -3;
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spTeamsInsert(101, 'checkers', 1, 'green', errorCode);
    spTeamsInsert(101, 'checkers', 1, 'green', errorCode);
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spTeamsInsert(102, 'checkers', 1, 'blue', errorCode);
END;


CREATE OR REPLACE PROCEDURE spTeamsUpdate(
    id teams.teamid%TYPE,
    name teams.teamname%TYPE,
    active teams.isactive%TYPE,
    colour teams.jerseycolour%TYPE,
    errorCode OUT INT
)AS
BEGIN
    UPDATE teams
    SET 
        teamid = id,
        teamname = name,
        isactive = active,
        jerseycolour = colour
    WHERE teamid = id;
    
    errorCode:=1;
    
    IF SQL%ROWCOUNT = 0 THEN
        errorCode := -1;
    END IF;
    
EXCEPTION WHEN OTHERS
    THEN errorCode:=-3;
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spTeamsUpdate(700, 'checkers', 1, 'green', errorCode);
    DBMS_OUTPUT.PUT_LINE('Code: ' || errorCode);
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spTeamsUpdate(225, 'chokers', 1, 'green', errorCode);
    DBMS_OUTPUT.PUT_LINE('Code: ' || errorCode);
END;


CREATE OR REPLACE PROCEDURE spTeamsDelete(
    id teams.teamid%TYPE,
    errorCode OUT INT
)AS
BEGIN
    DELETE teams
    WHERE teamid = id;
    errorCode := 1;
    
    IF SQL%ROWCOUNT = 0 THEN
        errorCode :=-1;
    END IF;
    
EXCEPTION WHEN OTHERS
    THEN errorCode:=-3;
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spTeamsDelete(500,errorCode);
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spTeamsDelete(400,errorCode);
END;

CREATE OR REPLACE PROCEDURE spTeamsSelect(
    id teams.teamid%TYPE,
    tRow OUT teams%ROWTYPE,
    errorCode OUT INT
)AS
BEGIN
    SELECT 
        teamid,
        teamname,
        isactive,
        jerseycolour
    INTO tRow
    FROM teams
    WHERE teamid = id;
        
    errorCode:=1;
   
EXCEPTION 
    WHEN NO_DATA_FOUND
        THEN errorCode:=-1;
    WHEN OTHERS
        THEN errorCode:=-3;
END;

DECLARE
    errorCode INT := 0;
    tRow teams%ROWTYPE;
BEGIN
    spTeamsSelect(500,tRow,errorCode);
END;

DECLARE
    errorCode INT := 0;
    tRow teams%ROWTYPE;
BEGIN
    spTeamsSelect(400,tRow,errorCode);
END;

CREATE OR REPLACE PROCEDURE spRostersInsert(
    pid rosters.playerid%TYPE,
    active rosters.isactive%TYPE,
    num rosters.jerseynumber%TYPE,
    tid rosters.teamid%TYPE,
    autoRosterID OUT rosters.rosterid%TYPE,
    errorCode OUT INT
    )AS
    autoID rosters.rosterid%TYPE;
BEGIN
    INSERT INTO rosters( playerid, teamid, isactive, jerseynumber)
    VALUES( pid, tid, active, num)
    RETURNING rosterid INTO autoRosterID;

    errorCode:=1;
    
EXCEPTION WHEN OTHERS
    THEN errorCode:=-3;
END;

DECLARE
    primaryKeyID rosters.rosterid%TYPE;
    errorCode INT := 0;
BEGIN
    spRostersInsert(100, 20, 139, 150, primaryKeyID, errorCode);
END;

CREATE OR REPLACE PROCEDURE spRostersUpdate(
    rid rosters.rosterid%TYPE,
    pid rosters.playerid%TYPE,
    tid rosters.teamid%TYPE,
    active rosters.isactive%TYPE,
    num rosters.jerseynumber%TYPE,
    errorCode OUT INT
)AS
BEGIN
    errorCode :=1;

    UPDATE rosters
    SET 
        rosterid = rid,
        playerid = pid,
        teamid = tid,
        isactive = active,
        jerseynumber = num
    WHERE rosterid = rid;
    
    IF SQL%ROWCOUNT = 0 THEN
        errorCode:=-1;
    END IF;
    
EXCEPTION WHEN OTHERS
    THEN errorCode :=-3;
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spRostersUpdate(250,100, 20, 139, 150, errorCode);
    DBMS_OUTPUT.PUT_LINE('Code: ' || errorCode);
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spRostersUpdate(15,100, 20, 139, 150, errorCode);
    DBMS_OUTPUT.PUT_LINE('Code: ' || errorCode);
END;

CREATE OR REPLACE PROCEDURE spRostersDelete(
    rid rosters.rosterid%TYPE,
    errorCode OUT INT
)AS
BEGIN
    errorCode:=1;

    DELETE rosters
    WHERE rosterid = rid;
    
    IF SQL%ROWCOUNT = 0 THEN
       errorCode:=-1;
    END IF;
    
EXCEPTION WHEN OTHERS
    THEN errorCode :=-3;
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spRostersDelete(15,errorCode);
END;

DECLARE
    errorCode INT := 0;
BEGIN
    spRostersDelete(260,errorCode);
END;


CREATE OR REPLACE PROCEDURE spRostersSelect(
    rid rosters.rosterid%TYPE,
    rRow OUT rosters%ROWTYPE,
    errorCode OUT INT
)AS
BEGIN
    SELECT
        rosterid,
        playerid,
        teamid,
        isactive,
        jerseynumber
    INTO rRow
    FROM rosters
    WHERE rosterid = rid;
   
    errorCode :=1;
  
EXCEPTION 
    WHEN NO_DATA_FOUND
        THEN errorCode:=-1;
    WHEN OTHERS
        THEN errorCode :=-3;
END;

DECLARE
    errorCode INT := 0;
     Rrow rosters%ROWTYPE;
BEGIN
    spRostersSelect(14,Rrow,errorCode);
END;

DECLARE
    errorCode INT := 0;
     Rrow rosters%ROWTYPE;
BEGIN
    spRostersSelect(260,Rrow,errorCode);
END;

/*
2. For each table in (Players, Teams, Rosters), create an additional Stored Procedure, 
called spTableNameSelectAll that outputs the contents of the table to the script window 
(using DBMS_OUTPUT) for the standard SELECT * FROM <tablename> statement.
*/

CREATE OR REPLACE PROCEDURE spPlayersSelectAll(errorCode OUT INT)
AS
    CURSOR projection IS
        SELECT *
        FROM players;
    row players%ROWTYPE;
BEGIN
    errorCode:=1;
    OPEN projection;
        DBMS_OUTPUT.PUT_LINE(RPAD('PlayerID',8, ' ' )|| ' ' || RPAD('Reg#',8,' ')||' ' ||RPAD('Last Name',10, ' ')||' ' ||RPAD('First Name',10,' ')||' '||RPAD('Active',6, ' '));
        DBMS_OUTPUT.PUT_LINE(RPAD('-',46, '-' ));
        LOOP
            FETCH projection INTO row;
            EXIT WHEN projection%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(RPAD(row.playerid,8, ' ' )|| ' ' || RPAD(row.regnumber,8,' ')||' ' ||RPAD(row.lastname,10, ' ')||' ' ||RPAD(row.firstname,10,' ')||' '||RPAD(row.isactive,4, ' '));
        END LOOP;
    CLOSE projection;

EXCEPTION WHEN OTHERS
    THEN errorCode:=-3;
END;

DECLARE 
    err INT;
BEGIN
    spPlayersSelectAll(err);
END;

CREATE OR REPLACE PROCEDURE spTeamsSelectAll(errorCode OUT INT)
AS
    CURSOR projection IS
        SELECT *
        FROM teams;
    row teams%ROWTYPE;
BEGIN
    errorCode :=1;
    OPEN projection;
        DBMS_OUTPUT.PUT_LINE(RPAD('TeamID',6, ' ' )|| ' ' || RPAD('TeamName',12,' ')||' ' ||RPAD('Active',6, ' ')||' '||RPAD('Jersey',14, ' '));
        DBMS_OUTPUT.PUT_LINE(RPAD('-',41, '-' ));
        LOOP
            FETCH projection INTO row;
            EXIT WHEN projection%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(RPAD(row.teamid, 6,' ') || ' ' ||RPAD(row.teamname,12,' ') ||' '||RPAD(row.isactive, 6, ' ')||' '||RPAD(row.jerseycolour,14,' '));
        END LOOP;
    CLOSE projection;

EXCEPTION WHEN OTHERS
    THEN errorCode :=-3;
END;

DECLARE
    err INT;
BEGIN
    spTeamsSelectAll(err);
END;

CREATE OR REPLACE PROCEDURE spRostersSelectAll(errorCode OUT INT)
AS
    CURSOR projection IS
        SELECT *
        FROM rosters;
    row rosters%ROWTYPE;
BEGIN
    errorCode :=1;
    OPEN projection;
        DBMS_OUTPUT.PUT_LINE(RPAD('Roster',6, ' ' )|| ' ' || RPAD('PlayerID',8, ' ' )||' ' ||RPAD('TeamID',6, ' ' )||' '|| RPAD('Active',6, ' ')|| ' '|| RPAD('Jersey#',7, ' '));
        DBMS_OUTPUT.PUT_LINE(RPAD('-',37, '-' ));
        LOOP
            FETCH projection INTO row;
            EXIT WHEN projection%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(RPAD(row.rosterid, 6, ' ') || ' ' || RPAD(row.playerid,8, ' ' )|| ' ' || RPAD(row.teamid, 6,' ') ||' '||RPAD(row.isactive, 6, ' ')||' '||RPAD(row.jerseynumber, 7, ' '));
        END LOOP;
    CLOSE projection;

EXCEPTION WHEN OTHERS
        THEN errorCode:=-3;
END;

DECLARE 
    err INT;
BEGIN
    spRostersSelectAll(err);
END;

/*
3.	Repeat Step 2 but returning the table in the output of the SP.  Use a non-saved procedure to show receiving the 
data and outputting it to the script window.  
NOTE: Some research will be required here as we did not cover this in class.
*/
CREATE OR REPLACE PROCEDURE spPlayersSelectAll(
    o_cursor OUT SYS_REFCURSOR, 
    errorCode OUT INT
)AS
BEGIN
    OPEN o_cursor FOR
        SELECT *
        FROM players;
        
    errorCode:=1;
    
EXCEPTION WHEN OTHERS
    THEN errorCode :=-3;
END;

CREATE OR REPLACE PROCEDURE spTeamsSelectAll(
    o_cursor OUT SYS_REFCURSOR,
    errorCode OUT INT)
AS
BEGIN
    OPEN o_cursor FOR
        SELECT *
        FROM teams;
    errorCode:=1;
    
EXCEPTION WHEN OTHERS
    THEN errorCode:=-3;
END;

CREATE OR REPLACE PROCEDURE spRostersSelectAll(
    o_cursor OUT SYS_REFCURSOR,
    errorCode OUT INT
)AS
BEGIN
    OPEN o_cursor FOR
        SELECT *
        FROM rosters;
        errorCode:=1;
        
EXCEPTION WHEN OTHERS
    THEN errorCode:=-3;
END;

DECLARE
    err INT;
    projection SYS_REFCURSOR;
    row players%ROWTYPE;
BEGIN
    spPlayersSelectAll(projection,err);
      DBMS_OUTPUT.PUT_LINE(RPAD('PlayerID',8, ' ' )|| ' ' || RPAD('Reg#',8,' ')||' ' ||RPAD('Last Name',10, ' ')||' ' ||RPAD('First Name',10,' ')||' '||RPAD('Active',6, ' '));
      DBMS_OUTPUT.PUT_LINE(RPAD('-',46, '-' ));
    LOOP
        FETCH projection INTO row;
        EXIT WHEN projection%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(row.playerid || ' ' || row.regnumber||' ' ||row.lastname||' ' ||row.firstname||' '||row.isactive);
    END LOOP;
END;

DECLARE
    err INT;
    projection2 SYS_REFCURSOR;
    row2 teams%ROWTYPE;
BEGIN
    spTeamsSelectAll(projection2, err);
    DBMS_OUTPUT.PUT_LINE(RPAD('TeamID',6, ' ' )|| ' ' || RPAD('TeamName',12,' ')||' ' ||RPAD('Active',6, ' ')||' '||RPAD('Jersey',14, ' '));
    DBMS_OUTPUT.PUT_LINE(RPAD('-',41, '-' ));
    LOOP
        FETCH projection2 INTO row2;
        EXIT WHEN projection2%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(row2.teamid || ' ' ||row2.teamname||' '||row2.isactive||' '||row2.jerseycolour);
    END LOOP;
END;

DECLARE
    projection3 SYS_REFCURSOR;
    row3 rosters%ROWTYPE;
    err INT;
BEGIN
    spRostersSelectAll(projection3, err);
    DBMS_OUTPUT.PUT_LINE(RPAD('Roster',6, ' ' )|| ' ' || RPAD('PlayerID',8, ' ' )||' ' ||RPAD('TeamID',6, ' ' )||' '|| RPAD('Active',6, ' ')|| ' '|| RPAD('Jersey#',7, ' '));
    DBMS_OUTPUT.PUT_LINE(RPAD('-',37, '-' ));
    LOOP
        FETCH projection3 INTO row3;
        EXIT WHEN projection3%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(row3.rosterid || ' ' || row3.playerid || ' ' || row3.teamid ||' '||row3.isactive||' '||row3.jerseynumber);
    END LOOP;
END;

/*4. Create a view which stores the “players on teams” information, called vwPlayerRosters 
which includes all fields from players, rosters, and teams in a single output table.  
You only need to include records that have exact matches.
*/
CREATE VIEW vwPlayerRosters AS
SELECT 
    p.playerid,
    p.regnumber,
    p.lastname,
    p.firstname,
    p.isactive,
    t.teamid,
    t.teamname,
    t.jerseycolour,
    r.rosterid,
    r.jerseynumber
FROM players p
JOIN rosters r ON p.playerid = r.playerid
JOIN teams t ON r.teamid = t.teamid
ORDER BY playerid;

/*
5.	Using the vwPlayerRosters view, create an SP, named spTeamRosterByID, that outputs, the team rosters, with names, 
    for a team given a specific input parameter of teamID
*/
CREATE OR REPLACE PROCEDURE spTeamRosterByID(
    tid teams.teamid%TYPE,
    errorCode OUT INT
)AS
    CURSOR projection IS
        SELECT *
        FROM vwPlayerRosters
        WHERE teamid = tid;
    row vwPlayerRosters%ROWTYPE;
    firstFetch BOOLEAN:= TRUE;
BEGIN
    errorCode :=1;
    OPEN projection;
        DBMS_OUTPUT.PUT_LINE(RPAD('PlayerID',8, ' ' )|| ' ' || RPAD('Reg#',6,' ')||' ' ||RPAD('Last-Name',10, ' ')||' '||RPAD('First-Name',10, ' ') ||' '||
        RPAD('Active',6, ' ')||' '||RPAD('TeamID', 6, ' ')||' '||RPAD('Team Name',12, ' ')|| ' '||RPAD('Jersey Colour', 14, ' ')||' '||
        RPAD('Roster', 6, ' ')||' '||RPAD('Jersey',6,' '));
        DBMS_OUTPUT.PUT_LINE(RPAD('-',88, '-' ));
        LOOP
            FETCH projection INTO row;
            IF projection%FOUND THEN
                firstFetch := FALSE;
            ELSIF firstFetch THEN
                errorCode :=-1;
            END IF;
            EXIT WHEN projection%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(RPAD(row.playerid, 8 ,' ') || ' ' || RPAD(row.regnumber,6,' ') || ' ' || RPAD(row.lastname,10, ' ') || ' ' || RPAD(row.firstname,10,' ') || ' '||
            RPAD(row.isactive, 6, ' ') || ' ' || RPAD(row.teamid, 6, ' ') || ' ' || RPAD(row.teamname, 12 , ' ') || ' '|| RPAD(row.jerseycolour,14, ' ') ||' '|| RPAD(row.rosterid,6, ' ') || ' ' || RPAD(row.jerseynumber, 6, ' '));
        END LOOP;
    CLOSE projection;

EXCEPTION WHEN OTHERS
    THEN errorCode:=-3;
END;

DECLARE 
    err INT;
BEGIN
    spTeamRosterByID(282,err);
    DBMS_OUTPUT.PUT_LINE(err);
END;

DECLARE 
    err INT;
BEGIN
    spTeamRosterByID(212,err);
END;

/*6.  Repeat task 4, by creating another similar stored procedure, named 
spTeamRosterByName, that receives a string parameter and returns the team roster, 
with names, for a team found through a search string.  The entered parameter 
may be any part of the name.

*/
CREATE OR REPLACE PROCEDURE spTeamRosterByName(
    name teams.teamname%TYPE,
    errorCode OUT INT
)AS
    CURSOR projection IS
        SELECT *
        FROM vwPlayerRosters
        WHERE UPPER(teamname) LIKE UPPER('%' || name || '%');
    row vwPlayerRosters%ROWTYPE;
    firstFetch BOOLEAN:=TRUE;
BEGIN
    errorCode:=1;
    OPEN projection;
        DBMS_OUTPUT.PUT_LINE(RPAD('PlayerID',8, ' ' )|| ' ' || RPAD('Reg#',6,' ')||' ' ||RPAD('Last-Name',10, ' ')||' '||RPAD('First-Name',10, ' ') ||' '||
        RPAD('Active',6, ' ')||' '||RPAD('TeamID', 6, ' ')||' '||RPAD('Team Name',12, ' ')|| ' '||RPAD('Jersey Colour', 14, ' ')||' '||
        RPAD('Roster', 6, ' ')||' '||RPAD('Jersey',6,' '));
        DBMS_OUTPUT.PUT_LINE(RPAD('-',88, '-' ));
        LOOP
            FETCH projection INTO row;
            IF projection%FOUND THEN
                firstFetch := FALSE;
            ELSIF firstFetch THEN
                errorCode :=-1;
            END IF;
            EXIT WHEN projection%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(RPAD(row.playerid, 8 ,' ') || ' ' || RPAD(row.regnumber,6,' ') || ' ' || RPAD(row.lastname,10, ' ') || ' ' || RPAD(row.firstname,10,' ') || ' '||
            RPAD(row.isactive, 6, ' ') || ' ' || RPAD(row.teamid, 6, ' ') || ' ' || RPAD(row.teamname, 12 , ' ') || ' '|| RPAD(row.jerseycolour,14, ' ') ||' '|| RPAD(row.rosterid,6, ' ') || ' ' || RPAD(row.jerseynumber, 6, ' '));
        END LOOP;
    CLOSE projection;

EXCEPTION 
    WHEN OTHERS
        THEN errorCode:=-3;
END;
 
DECLARE 
    err INT;
BEGIN
    spTeamRosterByName('aU',err);
END;
DECLARE 
    err INT;
BEGIN
    spTeamRosterByName('Strike',err);
END;
DECLARE 
    err INT;
BEGIN
    spTeamRosterByName('rangers',err);
END;

DECLARE 
    err INT;
BEGIN
    spTeamRosterByName('EAGLES',err);
END;

DECLARE 
    err INT;
BEGIN
    spTeamRosterByName('esonic',err);
END;

/*7. Create a view that returns the number of players currently registered on
each team, called vwTeamsNumPlayers.
*/
CREATE VIEW vwTeamsNumPlayers AS
SELECT 
  teamid,
  COUNT(playerid) AS numberOfPlayers
FROM rosters
GROUP BY teamid;

/*8.Using vwTeamsNumPlayers create a user defined function,
that given the team PK, will return the number of players currently registered,
called fncNumPlayersByTeamID.
*/
CREATE OR REPLACE FUNCTION fncNumPlayersByTeamID(tid teams.teamid%TYPE)
    RETURN NUMBER IS
    dummy NUMBER;
BEGIN
    SELECT
    numberOfPlayers INTO dummy
    FROM vwTeamsNumPlayers
    WHERE teamid = tid;
    RETURN dummy;
    
EXCEPTION 
    WHEN NO_DATA_FOUND
        THEN dummy:=-1;
            RETURN dummy;
    WHEN OTHERS
        THEN dummy:=-3;
            RETURN dummy;
END;


SELECT fncNumPlayersByTeamID(212) FROM DUAL;
SELECT fncNumPlayersByTeamID(622) FROM DUAL;

/*
9.    Create a view, called vwSchedule, that shows all games, but includes the written names for teams and locations, 
    in addition to the PK/FK values.  Do not worry about division here.
*/
CREATE OR REPLACE VIEW vwSchedule AS
SELECT
    gameid,
    divid,
    gamenum,
    gamedatetime,
    h.teamname AS home,
    homescore,
    v.teamname AS visiting,
    visitscore,
    l.locationname AS location,
    isplayed,
    notes
FROM games
LEFT JOIN teams h ON h.teamid = games.hometeam
LEFT JOIN sllocations l ON l.locationid = games.locationid
LEFT JOIN teams v ON games.visitteam = v.teamid
ORDER BY gameid;

/*
10.	Create a stored procedure, spSchedUpcomingGames, using DBMS_OUTPUT, that displays the games to be played in the 
    next n days, where n is an input parameter.  Make sure your code will work on any day of the year.
*/

SET SERVEROUTPUT ON
CREATE OR REPLACE PROCEDURE spSchedUpcomingGames(
    num INTEGER,
    errorCode OUT INT
)AS
    row vwSchedule%ROWTYPE;
    CURSOR display IS
        SELECT 
            gameid,
            divid,
            gamenum,
            gamedatetime,
            home,
            homescore,
            visiting,
            visitscore,
            location,
            isplayed,
            notes
        FROM vwSchedule
        WHERE gamedatetime >= sysdate 
        AND gamedatetime <= sysdate + num;
    firstFetch BOOLEAN:= TRUE;
BEGIN
    errorCode:=1;
    
      DBMS_OUTPUT.PUT_LINE(RPAD('GameID', 6, ' ')||' ' ||RPAD('DivID', 6, ' ') || ' ' ||RPAD('Game#', 5, ' ')|| ' '||RPAD('GameDate',8, ' ')
        ||' ' ||RPAD('HomeTeam',8,' ')||' '|| RPAD('HomeScore',9, ' ')|| ' '|| RPAD('Visiting',9,' ')|| ' ' ||RPAD('VisitScore',10,' ')||' '
        ||RPAD('Location',8, ' ')||' '||RPAD('Status',6, ' ')||' '||RPAD('Notes',15,' '));
    OPEN display;
        LOOP
            FETCH display INTO row;
            IF display%FOUND THEN
                firstFetch := FALSE;
            ELSIF firstFetch THEN
                errorCode :=-1;
            END IF;
            EXIT WHEN display%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(RPAD(row.gameid, 6, ' ')||' ' ||RPAD(row.divid, 6, ' ') || ' ' ||RPAD(row.gamenum, 5, ' ')|| ' '||RPAD(row.gamedatetime,8, ' ')
            ||' ' ||RPAD(row.home,8,' ')||' '|| RPAD(row.homescore,9, ' ')|| ' '|| RPAD(row.visiting,9,' ')|| ' ' ||RPAD(row.visitscore,10,' ')||' '
            ||RPAD(row.location,8, ' ')||' '||RPAD(row.isplayed,6, ' ')||' '||RPAD(row.notes,15,' '));
        END LOOP;
    CLOSE display;

EXCEPTION
    WHEN OTHERS
        THEN errorCode:=-3;
END;

DECLARE 
    err INT;
BEGIN
    spSchedUpcomingGames(5,err);
END;

DECLARE 
    err INT;
BEGIN
    spSchedUpComingGames(5,err);
END;

DECLARE 
    err INT;
BEGIN
    spSchedUpComingGames(1000,err);
END;


/*11.	Create a stored procedure, spSchedPastGames, using DBMS_OUTPUT, that displays the games that have been played
    in the past n days, where n is an input parameter.  Make sure your code will work on any day of the year.
*/

CREATE OR REPLACE PROCEDURE spSchedPastGames(
    num NUMBER,
    errorCode OUT INT
)AS
    row vwSchedule%ROWTYPE;
    firstFetch BOOLEAN:=TRUE;
    CURSOR display IS
        SELECT 
            gameid,
            divid,
            gamenum,
            gamedatetime,
            home,
            homescore,
            visiting,
            visitscore,
            location,
            isplayed,
            notes
        FROM vwSchedule
        WHERE gamedatetime <= sysdate 
        AND gamedatetime >= sysdate - num;
BEGIN
    errorCode:=1;
    OPEN display;
        DBMS_OUTPUT.PUT_LINE(RPAD('GameID', 6, ' ')||' ' ||RPAD('DivID', 6, ' ') || ' ' ||RPAD('Game#', 5, ' ')|| ' '||RPAD('GameDate',8, ' ')
        ||' ' ||RPAD('HomeTeam',8,' ')||' '|| RPAD('HomeScore',9, ' ')|| ' '|| RPAD('Visiting',9,' ')|| ' ' ||RPAD('VisitScore',10,' ')||' '
        ||RPAD('Location',8, ' ')||' '||RPAD('Status',6, ' ')||' '||RPAD('Notes',15,' '));
        LOOP
            FETCH display INTO row;
            IF display%FOUND THEN
                firstFetch := FALSE;
            ELSIF firstFetch THEN
                errorCode :=-1;
            END IF;
            EXIT WHEN display%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(RPAD(row.gameid, 6, ' ')||' ' ||RPAD(row.divid, 6, ' ') || ' ' ||RPAD(row.gamenum, 5, ' ')|| ' '||RPAD(row.gamedatetime,8, ' ')
            ||' ' ||RPAD(row.home,8,' ')||' '|| RPAD(row.homescore,9, ' ')|| ' '|| RPAD(row.visiting,9,' ')|| ' ' ||RPAD(row.visitscore,10,' ')||' '
            ||RPAD(row.location,8, ' ')||' '||RPAD(row.isplayed,6, ' ')||' '||RPAD(row.notes,15,' '));
        END LOOP;
    CLOSE display;

EXCEPTION 
    WHEN OTHERS 
        THEN errorCode:=-3;
END;
 
SELECT * FROM GAMES;
 
DECLARE
    err INT;
BEGIN
    spSchedPastGames(5,err);
END;

DECLARE
    err INT;
BEGIN
    spSchedPastGames(1000,err);
END;

/*12. Using the Standings calculation demo code provided earlier in the 
semester, create a Stored Procedure, named spRunStandings, that replaces a
temporary static table, named tempStandings, with the output of the SELECT
code provided. 
*/
CREATE TABLE tempStandings AS
(SELECT
        TheTeamID,
        (SELECT teamname FROM teams WHERE teamid = t.TheTeamID) AS teamname,
        SUM(GamesPlayed) AS GP,
        SUM(Wins) AS W,
        SUM(Losses) AS L,
        SUM(Ties) AS T,
        SUM(Wins)*3 + SUM(Ties) AS Pts,
        SUM(GoalsFor) AS GF,
        SUM(GoalsAgainst) AS GA,
        SUM(GoalsFor) - SUM(GoalsAgainst) AS GD
    FROM (
    -- from the home team perspective
        SELECT
            hometeam AS TheTeamID,
            COUNT(gameID) AS GamesPlayed,
            SUM(homescore) AS GoalsFor,
            SUM(visitscore) AS GoalsAgainst,
            SUM(
                CASE
                    WHEN homescore > visitscore THEN 1
                    ELSE 0
                    END
                ) As Wins,
            SUM(
                CASE
                    WHEN homescore < visitscore THEN 1
                    ELSE 0
                    END
                ) As Losses,
            SUM(
                CASE
                    WHEN homescore = visitscore THEN 1
                    ELSE 0
                    END
                ) As Ties    
        FROM games
        WHERE isPlayed = 1
        GROUP BY hometeam
       
        UNION ALL
       
        -- from the perspective of the visiting team
        SELECT
            visitteam AS TheTeamID,
            COUNT(gameID) AS GamesPlayed,
            SUM(visitscore) AS GoalsFor,
            SUM(homescore) AS GoalsAgainst,
            SUM(
                CASE
                    WHEN homescore < visitscore THEN 1
                    ELSE 0
                    END
                ) As Wins,
            SUM(
                CASE
                    WHEN homescore > visitscore THEN 1
                    ELSE 0
                    END
                ) As Losses,
            SUM(
                CASE
                    WHEN homescore = visitscore THEN 1
                    ELSE 0
                    END
                ) As Ties    
        FROM games
        WHERE isPlayed = 1
        GROUP BY visitteam ) t
    GROUP BY TheTeamID);

/*13.	Following up with Step 12, create a Trigger in the system to automate 
the execution of the spRunStandings SP when any row in the games table is updated. 
Essentially meaning that software can run SELECT * FROM tempStandings; 
and always have up to date standings.*/

CREATE OR REPLACE TRIGGER trgStandings
AFTER INSERT OR UPDATE ON games 
BEGIN
    DELETE FROM tempStandings;

    INSERT INTO tempStandings (
    
    SELECT 
        TheTeamID,
        (SELECT teamname FROM teams WHERE teamid = t.TheTeamID) AS teamname,
        SUM(GamesPlayed) AS GP,
        SUM(Wins) AS W,
        SUM(Losses) AS L,
        SUM(Ties) AS T,
        SUM(Wins)*3 + SUM(Ties) AS Pts,
        SUM(GoalsFor) AS GF,
        SUM(GoalsAgainst) AS GA,
        SUM(GoalsFor) - SUM(GoalsAgainst) AS GD
    FROM (
    -- from the home team perspective
        SELECT
            hometeam AS TheTeamID,
            COUNT(gameID) AS GamesPlayed,
            SUM(homescore) AS GoalsFor,
            SUM(visitscore) AS GoalsAgainst,
            SUM(
                CASE
                    WHEN homescore > visitscore THEN 1
                    ELSE 0
                    END
                ) As Wins, 
            SUM(
                CASE
                    WHEN homescore < visitscore THEN 1
                    ELSE 0
                    END
                ) As Losses,
            SUM(
                CASE
                    WHEN homescore = visitscore THEN 1
                    ELSE 0
                    END
                ) As Ties    
        FROM games
        WHERE isPlayed = 1
        GROUP BY hometeam
        
        UNION ALL
        
        -- from the perspective of the visiting team
        SELECT
            visitteam AS TheTeamID,
            COUNT(gameID) AS GamesPlayed,
            SUM(visitscore) AS GoalsFor,
            SUM(homescore) AS GoalsAgainst,
            SUM(
                CASE
                    WHEN homescore < visitscore THEN 1
                    ELSE 0
                    END
                ) As Wins, 
            SUM(
                CASE
                    WHEN homescore > visitscore THEN 1
                    ELSE 0
                    END
                ) As Losses,
            SUM(
                CASE
                    WHEN homescore = visitscore THEN 1
                    ELSE 0
                    END
                ) As Ties    
        FROM games
        WHERE isPlayed = 1
        GROUP BY visitteam ) t
    GROUP BY TheTeamID
    );
    
    EXCEPTION
        WHEN OTHERS THEN
            -- Log the error or handle it appropriately
            DBMS_OUTPUT.PUT_LINE('Error: General error');
END;

UPDATE games SET homescore = 10, visitscore = 1 WHERE gameid = 1;
SELECT * FROM tempStandings;

/*14.  Each group must be creative and come up with an object (SP, UDF, or 
potentially trigger), of your own choosing, that will be built in the database 
to help support the same ideals of the above objects.*/
CREATE OR REPLACE PROCEDURE spAvgGoalsTeam(
    tId games.hometeam%TYPE,
    numGoals OUT INT,
    errorCode OUT INT
)AS
BEGIN
    SELECT AVG(homescore + visitscore) AS avgGoals
    INTO numGoals
    FROM games
    WHERE (hometeam = tID AND isPlayed = 1) OR (visitteam = tID AND isPlayed = 1);
    
    errorCode:=1;
    
    IF numGoals IS NULL THEN
        errorCode:=-1;
    END IF;
    
EXCEPTION 
    WHEN OTHERS THEN
        errorCode:=-3;
END spAvgGoalsTeam;

DECLARE
    err INT;
    numGoals INT;
BEGIN
    spAvgGoalsTeam(600,numGoals,err);
END;

DECLARE
    err INT;
    numGoals INT;
BEGIN
    spAvgGoalsTeam(210,numGoals,err);
END;



 