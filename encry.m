function result=encry(in1)
x = dec2bin(in1);
y = dec2bin(15);
if length(x)~=length(y)
    max_len = max(length(x), length(y));
    x = [repmat('0', 1, max_len-length(x)), x];
    y = [repmat('0', 1, max_len-length(y)), y];
end
result = xor(x-'0', y-'0');
result=bin2dec(char(result + '0'));
end
%me = cell2mat(result).*1;
%me = double(result);
%me=int64(char(result));
%me=bin2dec(result)