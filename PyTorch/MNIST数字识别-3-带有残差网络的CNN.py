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

#残差网络
class ResidualBlock(torch.nn.Module):
    def __init__(self,channel):
        super(ResidualBlock, self).__init__()
        self.conv1=torch.nn.Conv2d(channel,channel,
                                   kernel_size=3,padding=1)
        self.conv2=torch.nn.Conv2d(channel,channel,
                                   kernel_size=3,padding=1)
    def forward(self,x):
        y=F.relu(self.conv1(x))
        y=self.conv2(x)
        return F.relu(y+x)



#编写带有卷积层的神经网络
class Net(torch.nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1=torch.nn.Conv2d(1,10,kernel_size=5)  #设置两个卷积层
        self.conv2=torch.nn.Conv2d(10,20,kernel_size=5)
        self.pooling=torch.nn.MaxPool2d(2)              #添加池化层，kernel_size=2，默认stride为2
        self.rb1=ResidualBlock(10)
        self.rb2=ResidualBlock(20)                      #设置残差网络
        self.fc=torch.nn.Linear(320,10)

    def forward(self,x):
        batch_size=x.size(0)
        x=self.pooling(F.relu(self.conv1(x)))
        x=self.rb1(x)
        x=self.pooling(F.relu(self.conv2(x)))
        x=self.rb2(x)
        x=x.view(batch_size,-1)  #改变x的行数为 每一batch中 样本的数量
        x=self.fc(x)
        return x

model=Net()
#指定使用GPU
device=torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
criterion=torch.nn.CrossEntropyLoss(size_average=True)
optimizer=torch.optim.SGD(model.parameters(),lr=0.01,momentum=0.5)
model.to(device)

def train(epoch):
    running_loss=0.0
    for index,data in enumerate(train_loader,0):
        inputs,target=data
        inputw,target=inputs.to(device),target.to(device)
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
        inputs,target=inputs.to(device),target.to(device)
        y_pred=model(inputs)
        _,predicted=torch.max(y_pred.data,dim=1)   #求矩阵每一行的最大值，dim=0表示按列求最值，dim=1表示按行求最值
        correct+=(target==predicted).sum().item()    #求预测正确的样本个数
        total+=target.shape[0]
    print('Accuracy on test set: %d %% [%d %d]' %(100*correct/total,correct,total))


if __name__=='__main__':
    for epoch in range(10):
        train(epoch)
        test()
