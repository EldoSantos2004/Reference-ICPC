
int n, numBlocks;
string s;

struct Block{
  int l, r;
  int sz(){ 
    return r-l;
  }
};

Block blocks[2*MAXI];
Block newBlocks[2*MAXI];

void rebuildDecomp(){
  string newS=s;
  int k=0;
  for(int i=0;i<numBlocks;i++){
    for(int j=blocks[i].l;j<blocks[i].r;j++){
      newS[k++]=s[j];
    }
  }
  numBlocks=1;
  blocks[0]={0, n};
  s=newS;
}

void cut(int a, int b){
  int pos=0, curBlock=0;
  for(int i=0;i<numBlocks;i++){
    Block B=blocks[i];
    bool containsA = pos < a && pos + B.sz() > a;
    bool containsB = pos < b && pos + B.sz() > b;
    int cutA = B.l + a - pos;
    int cutB = B.l + b - pos;
    if(containsA && containsB){
      newBlocks[curBlock++]={B.l, cutA};
      newBlocks[curBlock++]={cutA, cutB};
      newBlocks[curBlock++]={cutB, B.r};
    }
    else if(containsA){
      newBlocks[curBlock++]={B.l, cutA};
      newBlocks[curBlock++]={cutA, B.r};
    }
    else if(containsB){
      newBlocks[curBlock++]={B.l, cutB};
      newBlocks[curBlock++]={cutB, B.r};
    }
    else{
      newBlocks[curBlock++]=B;
    }
    pos += B.sz();
  }
  pos=0;
  numBlocks=0;
  for(int i=0;i<curBlock;i++){
    if(pos<a || pos>=b){
      blocks[numBlocks++]=newBlocks[i];
    }
    pos+=newBlocks[i].sz();
  }
  pos=0;
  for(int i=0;i<curBlock;i++){
    if(pos>=a && pos<b){
      blocks[numBlocks++]=newBlocks[i];
    }
    pos+=newBlocks[i].sz();
  }
}

// while doing operations
if(numBlocks>MAXI){
  rebuildDecomp();
}

// rebuild before final ans
rebuildDecomp();
cout << ans << endl;
