#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N=101;
const int M=N*N;
const int inf=2e9;
int n,m,s,t;
int cell[N+1];
struct node
{
	int next,to,flow;
}edge[(M+1)<<1];
int tot=1,head[N],now[N];
void add(int from,int to,int flow)
{
	tot++;
	edge[tot].to=to;
	edge[tot].flow=flow;
	edge[tot].next=head[from];
	head[from]=tot;

	tot++;
	edge[tot].to=from;
	edge[tot].flow=0;
	edge[tot].next=head[to];
	head[to]=tot;
}
int que[N];
int l,r;
int layer()
{
	for(int i=0;i<=t;i++)cell[i]=0;
	l=1,r=0;
	cell[s]=1;
	que[++r]=s;
	while(l<=r)
	{
		int u=que[l];
		l++;
		for(int i=head[u];i;i=edge[i].next)
		{
			int v=edge[i].to;
			if(edge[i].flow>0&&!cell[v])
			{
				cell[v]=cell[u]+1;
				que[++r]=v;
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
int dinic(int u,int flow)
{
	if(u==t)return flow;
	int ord=flow;
	for(int i=now[u];i&&flow;i=edge[i].next)
	{
		now[u]=i;
		int v=edge[i].to;
		int f=edge[i].flow;
		if(cell[v]==cell[u]+1&&f>0)
		{
			int nex=dinic(v,min(flow,f));
			if(!nex)cell[v]=0;
			else
			{
				flow-=nex;
				edge[i].flow-=nex;
				edge[i^1].flow+=nex;
			}
		}
	}
	return ord-flow;
}
char str[16];
int tree[1502][130];
int vis[1502],cnt;
void grow(int x)
{
	int len=strlen(str);
	int now=0;
	for(int i=0;i<len;i++)
	{
		if(!tree[now][str[i]])tree[now][str[i]]=++cnt;
		now=tree[now][str[i]];
	}
	vis[now]=x;
}
int climb()
{
	int len=strlen(str);
	int now=0;
	for(int i=0;i<len;i++)
	now=tree[now][str[i]];
	
	return vis[now];
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>str;
		grow(i);
	}
	int u,v;
	for(int i=1;i<=m;i++)
	{
		cin>>str;
		u=climb();
		cin>>str;
		v=climb();
		
	}
	while(layer())
	{
		memcpy(now,head,sizeof head);
	}
}
