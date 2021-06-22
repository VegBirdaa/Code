import torch

input_size=4  #input_size 为单词中字母的种类数
hidden_size=8
batch_size=1
seq_len=5
num_layers=2
num_class=4
embedding_size=10

idx2char=['e','h','l','o']
dic={'e':0,'h':1,'l':2,'o':3}
x_data=['h','e','l','l','o']
y_data=['o','h','l','e','l']

#input_size : (batch,seq_len)
x=[dic[each] for each in x_data]
#target size : (batch*seq_len)
y=[dic[each] for each in y_data]



inputs=torch.LongTensor(x).view(1,-1)
labels=torch.LongTensor(y)

#使用RNN
class RNNModel(torch.nn.Module):
    def __init__(self):
        super(RNNModel,self).__init__()
        self.emb=torch.nn.Embedding(input_size,embedding_size)  #字典中词的个数;embedding的维度
        self.rnn=torch.nn.RNN(input_size=embedding_size,hidden_size=hidden_size,num_layers=num_layers)
        self.fc=torch.nn.Linear(hidden_size,num_class)

    def forward(self,x):
        hidden=torch.zeros(num_layers, batch_size, hidden_size)
        x=self.emb(x)
        x=x.view(-1,batch_size,embedding_size)
        x,_= self.rnn(x,hidden)
        x=self.fc(x)
        return x.view(-1,num_class)




rnnnet=RNNModel()
criterion=torch.nn.CrossEntropyLoss()
optimizer=torch.optim.Adam(rnnnet.parameters(),lr=0.05)

#使用RNN 训练
for epoch in range(15):
    outputs=rnnnet(inputs)
    loss=criterion(outputs,labels)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    _,idx=outputs.max(dim=1)
    idx=idx.data.numpy()
    print('Predicted:',''.join([idx2char[each] for each in idx]),end='')
    print(', Epoch [%d/15] loss=%.4f' % (epoch+1,loss.item()))
