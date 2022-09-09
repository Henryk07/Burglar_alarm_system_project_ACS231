% Title: Burglar Alarm System Implementation for ACS233
% 
% Authors:
% Jiazhen Haung 
% Mohamed Saafan
% Haolin Chen
% Austin Ng
% 
% Date: 18/05/2022
% 
% Description:
% This program is used to implement a burglar alarm system using communication between sensors, Arduino and MATLAB, and is written in C++. The objects used in this project are a magnetic sensor (for the window), Solenoid (for door lock), PIR sensor (for motion detection), WEBCAM (for facial recognition), keyboard (for user input, e.g., PIN), and a buzzer for alarming the user in case of burglary. A menu for the user is designed and is communicating to all other objects. 



function [order] = m_Message()
if ~isempty(instrfind)
fclose(instrfind);
delete(instrfind);
end
device = serialport('COM4', 9600);
char m_order='z';
m_exit=1;
pause(1);
f=figure;
sys_lock=0;
while m_exit
figure(f); % set figure to the top level
pause(1.5);

%read hardware status
write(device,'1',"char");
magswitch=read(device,1,"char"); % Reading magnetic switch (0 or 1)
write(device,'1',"char");
pir=read(device,1,"char"); % Reading PIR(0 or 1)

if magswitch=='1'&&pir=='1'
   disp("PIR Detected Movement And Window is open");
elseif magswitch=='1'
   disp("Magswitch is Open!");
elseif pir=='1'
   disp("Motion Detected!");
end



write(device,'1',"char"); %Informing Arduino to move to next step




pause(0.5);
m_PIR=read(device,1,"char");
%1 fr
if m_PIR=='1' % If motion Detected
   faceresult=streamingFaceRecognition(); % Start Facial Recognition and Identify faces
   %faceresult=0;
   write(device,faceresult,"char"); %Send results to comparison 
   if faceresult==1 
   set(gcf,'CurrentCharacter','e'); % Set the current character as e to the figure
   end
elseif m_PIR=='0'%do nothing and keepgoing
    disp("here");
    if sys_lock==1
        %set(gcf,'CurrentCharacter','e');
        sys_lock=0; %Sys unlocked
    end
    write(device,'0',"char");
elseif m_PIR=='2'%system locked
     pause(0.5);
     if  device.NumBytesAvailable>0
        disp(read(device,device.NumBytesAvailable,"string")); % Display input from arduino with the required length
     end
     set(gcf,'CurrentCharacter','e');
     sys_lock=1;
end

%% Defining Menu based on user command
if strcmpi(get(gcf,'CurrentCharacter'),'e') % Get the current character from the figure and compare with e (to open the menu)
    if sys_lock==0
    m_order=input("enter the order","s");
    write(device,m_order,"char");
    elseif sys_lock==1
        m_order='z'; %System Locked/idle
        write(device,m_order,"char");
    end
else
    m_order='z';
    write(device,m_order,"char");
end
set(gcf,'CurrentCharacter','@'); %set current character to virtual key

switch m_order
    case 's' % Activate Hardware 
        m_pin=input("Enter PIN or B to go back to Homepage:  ",'s');
        if m_pin=='B' 
           write(device,'B',"char");
           write(device,'B',"char");
           pause(0.5);
           if  device.NumBytesAvailable>0
                disp(read(device,device.NumBytesAvailable,"string"));
           end
        % Formatting input into PIN Format:
        elseif (~isempty(str2num(m_pin)))&&(~isempty(0<str2num(m_pin)))...
                &&(~isempty(str2num(m_pin)<10000))&&numel(num2str(str2num(m_pin)))<5
        firstpin=fix(str2num(m_pin)/100);
        secondpin=fix(str2num(m_pin)-firstpin*100);
        firstpin=encry(firstpin);
        secondpin=encry(secondpin);
        write(device,firstpin,"char"); %Sending PIN to Arduino
        write(device,secondpin,"char");

        pause(0.5);
        if  device.NumBytesAvailable>0
        disp(read(device,device.NumBytesAvailable,"string"));
        end
        else
            write(device,'B',"char");
            write(device,'B',"char");
            disp("PIN Format Incorrect! Please Enter four digits");
            pause(0.5);
            if  device.NumBytesAvailable>0
               disp(read(device,device.NumBytesAvailable,"string"));
            end
        end
    case 'e' %Deactivate Hardware
        m_pin=input("Enter PIN or 'B' to go back to Homepage:  ",'s');
        if m_pin=='B'
           write(device,'B',"char");
           write(device,'B',"char");
           pause(0.5);
           if  device.NumBytesAvailable>0
            disp(read(device,device.NumBytesAvailable,"string"));
           end
        elseif (~isempty(str2num(m_pin)))&&(~isempty(0<str2num(m_pin)))...
                &&(~isempty(str2num(m_pin)<10000))&&numel(num2str(str2num(m_pin)))<5
        firstpin=fix(str2num(m_pin)/100);
        secondpin=fix(str2num(m_pin)-firstpin*100);
        firstpin=encry(firstpin);
        secondpin=encry(secondpin);
        write(device,firstpin,"char");
        write(device,secondpin,"char");
        pause(0.5);
        if  device.NumBytesAvailable>0
        disp(read(device,device.NumBytesAvailable,"string"));
        end
        else
            write(device,'B',"char");
            write(device,'B',"char");
            disp("PIN Format Incorrect! Please Enter four digits");
            pause(0.5);
            if  device.NumBytesAvailable>0
               disp(read(device,device.NumBytesAvailable,"string"));
            end
        end
    case 'c' %Changing Password
        m_pin=input("Enter PIN or 'B' to go back to Homepage:  ",'s');
        if m_pin=='B'
           write(device,'B',"char");
           write(device,'B',"char");
           pause(0.5);
           if  device.NumBytesAvailable>0
            disp(read(device,device.NumBytesAvailable,"string"));
           end
        elseif (~isempty(str2num(m_pin)))&&(~isempty(0<str2num(m_pin)))...
                &&(~isempty(str2num(m_pin)<10000))&&numel(num2str(str2num(m_pin)))<5
        firstpin=fix(str2num(m_pin)/100);
        secondpin=fix(str2num(m_pin)-firstpin*100);
        firstpin=encry(firstpin);
        secondpin=encry(secondpin);
        write(device,firstpin,"char");
        write(device,secondpin,"char");
        pause(0.5);
        %pin recover page
        if  device.NumBytesAvailable>0
        disp(read(device,device.NumBytesAvailable,"string"));
        end
        write(device,'1',"char");
        isnewpinorder=0;
        pause(0.5);
        if  device.NumBytesAvailable>0
        isnewpinorder=read(device,1,"char");
        end
            if isnewpinorder=='1'
               while 1
               m_newpin=input("Please Enter a four Digits PIN: ",'s');
               if (~isempty(str2num(m_newpin)))&&(~isempty(0<str2num(m_newpin)))...
                       &&(~isempty(str2num(m_newpin)<10000))...
                       &&numel(num2str(str2num(m_newpin)))<5
               firstpin=fix(str2num(m_newpin)/100);
               secondpin=fix(str2num(m_newpin)-firstpin*100);
               firstpin=encry(firstpin);
               secondpin=encry(secondpin);
               write(device,firstpin,"char");
               write(device,secondpin,"char");
               pause(0.5);
               if  device.NumBytesAvailable>0
                    disp(read(device,device.NumBytesAvailable,"string"));
               end
               break;
               end
               end
            else
               pause(0.5);
               if  device.NumBytesAvailable>0
                    disp(read(device,device.NumBytesAvailable,"string"));
               end
               write(device,1,"char");
            end
        else
            write(device,'B',"char");
            write(device,'B',"char");
            disp("PIN Format Incorrect! Please Enter four digits");
            pause(0.5);
            if  device.NumBytesAvailable>0
               disp(read(device,device.NumBytesAvailable,"string"));
            end
        end
    case 'r'
        m_pin=input("Enter PIN or B to go back to Homepage:  ",'s');
        if m_pin=='B'
           write(device,'B',"char");
           write(device,'B',"char");
           pause(0.5);
           if  device.NumBytesAvailable>0
            disp(read(device,device.NumBytesAvailable,"string"));
           end
        elseif (~isempty(str2num(m_pin)))&&(~isempty(0<str2num(m_pin)))...
                &&(~isempty(str2num(m_pin)<10000))&&numel(num2str(str2num(m_pin)))<5
        firstpin=fix(str2num(m_pin)/100);
        secondpin=fix(str2num(m_pin)-firstpin*100);
        firstpin=encry(firstpin);
        secondpin=encry(secondpin);
        write(device,firstpin,"char");
        write(device,secondpin,"char");
        pause(0.5);
        if  device.NumBytesAvailable>0
            temstring=read(device,device.NumBytesAvailable,"string");
            disp(temstring);
            if strcmp(temstring,"PIN Correct")
                new_pin=input("Enter the pin number of the LED",'s');
                write(device,str2num(new_pin),"char");
                pause(0.5);
                if  device.NumBytesAvailable>0
                    disp(read(device,device.NumBytesAvailable,"string"));
                end
            end
        end
        else
            write(device,'B',"char");
            write(device,'B',"char");
            disp("PIN Format Incorrect! Please Enter four digits");
            pause(0.5);
            if  device.NumBytesAvailable>0
               disp(read(device,device.NumBytesAvailable,"string"));
            end
        end
    case 'g'
        m_pin=input("Enter PIN or B to go back to Homepage:  ",'s');
        if m_pin=='B'
           write(device,'B',"char");
           write(device,'B',"char");
           pause(0.5);
           if  device.NumBytesAvailable>0
            disp(read(device,device.NumBytesAvailable,"string"));
           end
        elseif (~isempty(str2num(m_pin)))&&(~isempty(0<str2num(m_pin)))...
                &&(~isempty(str2num(m_pin)<10000))&&numel(num2str(str2num(m_pin)))<5
        firstpin=fix(str2num(m_pin)/100);
        secondpin=fix(str2num(m_pin)-firstpin*100);
        firstpin=encry(firstpin);
        secondpin=encry(secondpin);
        write(device,firstpin,"char");
        write(device,secondpin,"char");
        pause(0.5);
        if  device.NumBytesAvailable>0
            temstring=read(device,device.NumBytesAvailable,"string");
            disp(temstring);
            if strcmp(temstring,"PIN Correct")
                new_pin=input("Enter the pin number of the LED",'s');
                write(device,str2num(new_pin),"char");
                pause(0.5);
                if  device.NumBytesAvailable>0
                    disp(read(device,device.NumBytesAvailable,"string"));
                end
            end
        end
        else
            write(device,'B',"char");
            write(device,'B',"char");
            disp("PIN Format Incorrect! Please Enter four digits");
            pause(0.5);
            if  device.NumBytesAvailable>0
               disp(read(device,device.NumBytesAvailable,"string"));
            end
        end
    otherwise
        %write(device,'z',"char");
end


%disp(read(device,1,"char"));
order=m_order;        
end
clear device;
end