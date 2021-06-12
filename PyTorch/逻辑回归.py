import torch
import torch.nn.functional as F
x_data=torch.Tensor([[2.0,1.0],[3.0,2.0],[2.0,6.0],[6.6,7.0],[10.0,10.0]])
y_data=torch.Tensor([[1],[1],[0],[0],[1]])

class LogisticRegressionModel(torch.nn.Module):
    def __init__(self):
        super(LogisticRegressionModel,self).__init__()
        self.linear=torch.nn.Linear(2,1)

    def forward(self,x):
        y_pred=F.sigmoid(self.linear(x))
        return y_pred

model=LogisticRegressionModel()

criterion=torch.nn.BCELoss(size_average=False)
optimizer=torch.optim.SGD(model.parameters(),lr=0.01)

for epoch in range(1000):
    y_pred=model(x_data)
    loss=criterion(y_pred,y_data)
    print(epoch,loss.item())

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
    
#print(x>=y)
y_test=model(torch.Tensor([[6.9,4.0],[2.0,1.0],[5.0,6.0]]))
for each in y_test.data:
    if each > 0.5:
        print(1)
    else:
        print(0)
