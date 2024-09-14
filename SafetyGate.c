//Only want to check modification from git
//Wait init lock groups data
IF sv_bInitDone THEN
    iCnt := iCnt+1;
    IF (iCnt > iCntMax) THEN //3
        sv_bStartLockGroupInit := TRUE;
        STOP_PROCESS_ALGORITHM();  
    END_IF;     
END_IF;
// Core In out 
FOR  i := 1 TO 8 DO
    bNoFUCoreIn[i]:= TRUE;
    bNoFUCoreOut[i] := TRUE;
    Index_No_CoreIn[i] := 0;
    Index_No_CoreOut[i] := 0;

    pDeviceId := GET_SYNC_REFTO(CONCAT('Core',INT_TO_STRING(i),'.sv_DeviceId'), T#0s, s);
    IF s = KSYS_Status_OK THEN
       mpMoveLockGrpCoreIn[i].sMoveLckGrp := GET_SYNC_REFTO(CONCAT('Core',INT_TO_STRING(i),'.sv_MoveIn.LockGroups'),T#0s,Stat);
       mpMoveLockGrpCoreOut[i].sMoveLckGrp := GET_SYNC_REFTO(CONCAT('Core',INT_TO_STRING(i),'.sv_MoveOut.LockGroups'),T#0s,Stat);
       bNoFUCoreIn[i]:= FALSE;
       bNoFUCoreOut[i] := FALSE;
        
       FOR k := 1 TO 10 DO
           IF mpMoveLockGrpCoreIn[i].sMoveLckGrp^[k]= cLockGroupSafetyGateMold THEN
                Index_No_CoreIn[i] := k;
           END_IF;
           IF mpMoveLockGrpCoreOut[i].sMoveLckGrp^[k]= cLockGroupSafetyGateMold THEN
                Index_No_CoreOut[i] := k;
           END_IF;
       END_FOR;
    END_IF;
END_FOR;
