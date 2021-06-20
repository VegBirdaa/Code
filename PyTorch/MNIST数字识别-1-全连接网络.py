import torch
import torch.nn.functional as F
from torchvision.transforms import transforms
from torchvision import datasets
from torch.utils.data import DataLoader


batch_size=64

#transforms.compose参数是一个列表，列表的每一项代表着一个操作
#Normalize：Normalized an tensor image with mean and standard deviation
#ToTensor：convert a PIL image to tensor (H*W*C) in range [0,255] to a torch.Tensor(C*H*W) in the range [0.0,1.0]

transform=transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.1307,),(0.3081,))
])
#下载训练集
train_dataset=datasets.MNIST(root='D:/MNIST',
                             train=True,
                             download=False,
                             transform=transform)
#使用DataLoader处理训练集
train_loader=DataLoader(dataset=train_dataset,
                        shuffle=True,
                        batch_size=batch_size)
#下载测试集
test_dataset=datasets.MNIST(root='D:/MNIST',
                            train=False,
                            download=False,
                            transform=transform)
#使用DataLoader处理测试集
test_loader=DataLoader(dataset=test_dataset,
                       shuffle=False,
                       batch_size=batch_size)
#编写神经网络
class Net(torch.nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.l1=torch.nn.Linear(784,512)
        self.l2=torch.nn.Linear(512,256)
        self.l3=torch.nn.Linear(256,128)
        self.l4=torch.nn.Linear(128,64)
        self.l5=torch.nn.Linear(64,10)

    def forward(self,x):
        x=x.view(-1,784)
        x=F.relu(self.l1(x))
        x=F.relu(self.l2(x))
        x=F.relu(self.l3(x))
        x=F.relu((self.l4(x)))
        return self.l5(x)

model=Net()
criterion=torch.nn.CrossEntropyLoss(size_average=True)
optimizer=torch.optim.SGD(model.parameters(),lr=0.01,momentum=0.5)

def train(epoch):
    running_loss=0.0
    for index,data in enumerate(train_loader,0):
        inputs,target=data
        optimizer.zero_grad()
        #forward + backward + update
        y_pred=model(inputs)
        loss=criterion(y_pred,target)
        loss.backward()
        optimizer.step()

        running_loss+=loss.item()
        if index % 300==299:
            print('[%d,%5d] loss: %.3f' %(epoch+1,index,running_loss/300))
            running_loss=0.0

def test():
    total=0
    correct=0
    for data in test_loader:
        inputs,target=data
        y_pred=model(inputs)
        _,predicted=torch.max(y_pred.data,dim=1)   #求矩阵每一行的最大值，dim=0表示按列求最值，dim=1表示按行求最值
        correct+=(target==predicted).sum().item()    #求预测正确的样本个数
        total+=target.shape[0]
    print('Accuracy on test set: %d %%' %(100*correct/total))


if __name__=='__main__':
    for epoch in range(10):
        train(epoch)
    test()
