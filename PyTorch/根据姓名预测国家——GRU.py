import csv
import gzip
import math
import time

from torch.nn.utils.rnn import pack_padded_sequence

from torch.utils.data import DataLoader,Dataset
import torch
import matplotlib.pyplot as plt

BATCH_SIZE=256
HIDDEN_SIZE=100
N_LAYER=2
N_EPOCHES=100
N_CHARS=128
USE_GPU=False

class NameDataset(Dataset):
    def __init__(self,is_train_set=True):
        filename='data/names_train.csv.gz' if is_train_set else 'data/names_test.csv.gz'
        with  gzip.open(filename,'rt') as f:
            reader=csv.reader(f)
            rows=list(reader)
        self.names=[row[0] for row in rows]
        self.len=len(self.names)
        self.countries=[row[1] for row in rows]
        self.countrie_list=list(sorted(set(self.countries)))
        self.countrie_dict=self.getCountryDict()
        self.country_num=len(self.countrie_list)

    def __getitem__(self, index):
        return self.names[index],self.countrie_dict[self.countries[index]]

    def __len__(self):
        return self.len

    def getCountryDict(self):
        country_dict=dict()
        for idx,country in enumerate(self.countrie_list):
            country_dict[country]=idx;
        return country_dict

    def idx2country(self,idx):
        return self.countrie_list[idx]

    def getCountriesNum(self):
        return self.country_num


trainset=NameDataset(True)
trainloader=DataLoader(dataset=trainset,batch_size=BATCH_SIZE,shuffle=True)
testset=NameDataset(False)
testloader=DataLoader(dataset=testset,batch_size=BATCH_SIZE,shuffle=False)

N_COUNTRY=trainset.getCountriesNum()

def create_tensor(tensor):
    if USE_GPU:
        device=torch.device("cuda:0")
        tensor=tensor.to(device)
    return tensor

def time_since(since):
    s=time.time()-since
    m=math.floor(s/60)
    s-=m*60
    return '%dm %ds'%(m,s)

class RNNClassifier(torch.nn.Module):
    def __init__(self,input_size,hidden_size,output_size,n_layers=1,bidirectional=True):
         super(RNNClassifier,self).__init__()
         self.hidden_size=hidden_size
         self.n_layers=n_layers
         self.n_directions=2 if bidirectional else 1

         self.embedding=torch.nn.Embedding(input_size,hidden_size)
         self.gru=torch.nn.GRU(input_size=hidden_size,hidden_size=hidden_size,
                               num_layers=n_layers,bidirectional=bidirectional)
         self.fc=torch.nn.Linear(hidden_size*self.n_directions,output_size)

    def _ini_hidden(self,batch_size):
        hidden=torch.zeros(self.n_layers*self.n_directions,batch_size,self.hidden_size)
        return create_tensor(hidden)

    def forward(self,input,seq_lengths):
        input=input.t()
        batch_size=input.size(1)

        hidden=self._ini_hidden(batch_size)
        embedding=self.embedding(input)
        gru_input=pack_padded_sequence(embedding,seq_lengths)

        output,hidden=self.gru(gru_input,hidden)
        if self.n_directions==2:
            hidden_cat=torch.cat([hidden[-1],hidden[-2]],dim=1)
        else:
            hidden_cat=hidden[-1]

        fc_output=self.fc(hidden_cat)
        return fc_output

def name2list(name):
    arr=[ord(each) for each in name]
    return arr,len(arr)

def make_tensors(names,countries):
    sequence_and_lengths=[name2list(name) for name in names]
    name_sequences=[each[0] for each in sequence_and_lengths]
    seq_lengths=torch.LongTensor([each[1] for each in sequence_and_lengths])
    countries=countries.long()

    #make name Tensor
    seq_tensor=torch.zeros(len(name_sequences),seq_lengths.max()).long()
    for idx,(seq,seq_len) in enumerate(zip(name_sequences,seq_lengths),0):
        seq_tensor[idx,:seq_len]=torch.LongTensor(seq)

    #sort by lenght to use pack_padded_sequence
    seq_lengths,perm_idx=seq_lengths.sort(dim=0,descending=True)
    seq_tensor=seq_tensor[perm_idx]
    countries=countries[perm_idx]

    return create_tensor(seq_tensor),\
           create_tensor(seq_lengths),\
           create_tensor(countries)



def trainModel(epoch):
    total_loss=0
    for i,(names,countries) in enumerate(trainloader,1):
        inputs,seq_lenghts,target=make_tensors(names,countries)
        output=classifier(inputs,seq_lenghts)
        loss=criterion(output,target)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        total_loss+=loss.item()

        if i%10==0:
            print(f'[{time_since(start)}] Epoch {epoch}',end='')
            print(f'[{i*len(inputs)}/{len(trainset)}]',end='')
            print(f'loss={total_loss/(i*len(inputs))}')

    return total_loss

def testModel():
    correct=0
    total=len(testset)
    print('evaluating trained model...')

    with torch.no_grad():
        for i,(names,countries) in enumerate(testloader,1):
            inputs,seq_lengths,target=make_tensors(names,countries)
            output=classifier(inputs,seq_lengths)
            pred=output.max(dim=1,keepdim=True)[1]
            correct+=pred.eq(target.view_as(pred)).sum().item()
        percent='%.2f'%(100*correct/total)
        print(f'Test set:Accuracy {correct}/{total} {percent}%')

    return correct/total

if __name__=='__main__':
    classifier = RNNClassifier(N_CHARS, HIDDEN_SIZE, N_COUNTRY, N_LAYER)
    if USE_GPU:
        device=torch.device("cuda:0")
        classifier.to(device)

    criterion = torch.nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(classifier.parameters(), lr=0.01)
    start=time.time()
    print('Training for %d epoches...'% N_EPOCHES)
    acc_list=[]

    for epoch in range(1,N_EPOCHES+1):
        trainModel(epoch)
        acc=testModel()
        acc_list.append(acc)

x=range(1,N_EPOCHES+1)
plt.plot(x,acc_list)
plt.show()
