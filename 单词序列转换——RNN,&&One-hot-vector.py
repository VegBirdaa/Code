import torch

input_size=4
hidden_size=4
batch_size=1
seq_len=5
num_layers=1

idx2char=['e','h','l','o']
dic={'e':0,'h':1,'l':2,'o':3}
x_data=['h','e','l','l','o']
y_data=['o','h','l','e','l']

#独热向量字典
one_hot_lookup=[
    [1,0,0,0],
    [0,1,0,0],
    [0,0,1,0],
    [0,0,0,1]
]
x=[one_hot_lookup[dic[each]] for each in x_data]
y=[dic[each] for each in y_data]

inputs=torch.Tensor(x).view(-1,batch_size,input_size)
labels=torch.LongTensor(y).view(-1,1)

#建立模型，使用RNNCell
class Model(torch.nn.Module):
    def __init__(self):
        super(Model, self).__init__()
        self.rnncell=torch.nn.RNNCell(input_size=input_size,hidden_size=hidden_size)

    def forward(self,input,hidden):
        hidden=self.rnncell(input,hidden)
        return hidden

    def ini_hidden(self):
        return torch.zeros(batch_size,hidden_size)

net=Model()

#criterion=torch.nn.CrossEntropyLoss()
#optimizer=torch.optim.Adam(net.parameters(),lr=0.01)

# #训练 使用RNNCell
# for epoch in range(100):
#     loss=0      #初始化损失
#     hidden=net.ini_hidden()         #设置h0
#     optimizer.zero_grad()
#     print('Predicted string:',end='')
#     for input,label in zip(inputs,labels):
#         hidden=net(input,hidden)
#         loss+=criterion(hidden,label)  #对每个seq的损失求和
#         _,idx=hidden.max(dim=1)
#         print(idx2char[idx.item()],end='')
#     loss.backward()
#     optimizer.step()
#     print(', Epoch [%d/15] loss=%.4f'%(epoch+1,loss.item()))


#使用RNN
class RNNModel(torch.nn.Module):
    def __init__(self):
        super(RNNModel,self).__init__()
        self.rnn=torch.nn.RNN(input_size=input_size,hidden_size=hidden_size,num_layers=num_layers)

    def forward(self,input):
        hidden=torch.zeros(num_layers, batch_size, hidden_size)
        out,_= self.rnn(input,hidden)
        return out.view(-1,hidden_size)



rnnnet=RNNModel()
criterion=torch.nn.CrossEntropyLoss()
optimizer=torch.optim.Adam(rnnnet.parameters(),lr=0.05)

labels=torch.LongTensor(y)
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
