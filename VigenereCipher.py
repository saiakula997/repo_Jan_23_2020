class VigenereCipher(object):
    def __init__(self, key):
        print('Vigenere Cipher Encription')
        self.key=key
    
    def encode(self, text):    
        key=self.key
        ans=''
        for I,i in enumerate(text):
            if(ord('!')<=ord(i)<=ord('~')):
                I=I%len(key)
                if( ord(i)+ord(key[I])-ord('!') > ord('~') ):
                    ans+=(chr(ord('!')+(ord(i)+ord(key[I])-ord('!'))%ord('~')-1))
                else:
                    ans+=(chr(ord(i)+ord(key[I])-ord('!')))
            else:
                ans+=i
        return ans
    
    def decode(self, text):     
        key=self.key
        ans=''
        for I,i in enumerate(text):
            if(ord('!')<=ord(i)<=ord('~')):
                I=I%len(key)
                if( (ord('!')+ord(i)-ord(key[I])) < ord('!')):
                    ans+=(chr( ord('~')+(ord(i)-ord(key[I]))+1))
                else:
                    ans+=(chr( ord('!')+ord(i)-ord(key[I])))
            else:
                ans+=i
        return ans

def read_from_file(file_name):
    f=open(file_name,'r')
    data=f.read()
    f.close()
    return data

def write_to_file(file_name,data):
    f=open(file_name,'w')
    data=f.write(data)
    f.close()
    
import argparse    
parser = argparse.ArgumentParser(description='Description of your program')
parser.add_argument('-i','--input_file', help='input file name', required=True)
parser.add_argument('-e','--encode', help='encode password', required=False)
parser.add_argument('-d','--decode', help='decode password', required=False)
parser.add_argument('-s','--strength', help='strength of encription', type=int, default=1, required=False)
args = vars(parser.parse_args())

data=read_from_file(args.input_file)

if(args.encode):
    obj=VigenereCipher(args.encode)
    for _ in range(args.strength):
        data=obj.encode(data)
    write_to_file('encode.txt',data)
    print('written into file encode.txt')  
elif(args.decode):
    obj=VigenereCipher(args.decode)
    for _ in range(args.strength):
        data=obj.encode(data)
    write_to_file('decode.txt',data)    
    print('written into file decode.txt')
else:
    print('Need --encode or --decode password \nUse -h for help')


