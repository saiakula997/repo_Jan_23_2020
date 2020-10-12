class VigenereCipher(object):
    def __init__(self, key):
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


