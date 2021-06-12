import torch

#准备数据，用转换成tensor格式
x_data=torch.Tensor([[1.0],[2.0],[3.0]])
y_data=torch.Tensor([[2.0],[4.0],[6.0]])

class LinearModel(torch.nn.Module):
    def __init__(self):
        super(LinearModel,self).__init__()
        self.linear=torch.nn.Linear(1,1) #(size of in_features,size of out_features,bias=True)
    #前向计算
    def forward(self,x):
        y_pred=self.linear(x)
        return y_pred

model=LinearModel()

#构造损失函数
criterion=torch.nn.MSELoss(size_average=False) #不求均值
#构造优化器
optimizer=torch.optim.SGD(model.parameters(),lr=0.01) #固定的学习率

for epoch in range(1000):
    #计算y_head
    y_pred=model(x_data)
    #计算损失
    loss=criterion(y_pred,y_data)
    print(epoch,loss)
    #梯度清零
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
#输出w,b
print('w= ',model.linear.weight.item())
print('b= ',model.linear.bias.item())

x_test=torch.Tensor([[4.0]])
y_test=model(x_test)
print('y_pred= ',y_test.data)
