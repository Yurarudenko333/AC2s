from graphviz import Digraph
import os
os.environ['PATH'] += os.pathsep + 'E:/Programs/graphviz-2.38/release/bin/'
class Node:
    def __init__(self, branching_factor, is_leaf:bool = True):
        self.leaf = is_leaf
        self.key_num = 0
        self.key = [None for i in range(2*branching_factor+1)]
        self.child = [None for i in range(2*branching_factor+1)]
        self.pointers = [None for i in range(2*branching_factor+1)]

        self.right = self
        self.left = self
        self.parent = None
    def contains(self, key):
        try:
            self.key.index(key)
            return True
        except ValueError:
            return False

    def get_sibling(self,dir='left'):
      
        parent = self.parent
        if not(parent):
            return None
        i = 0
        while parent.child[i] is not self:
            i += 1
        left_sibling = parent.child[i-1] if i > 0 else None
        right_sibling = parent.child[i+1] if i< parent.key_num else None
        if dir == 'left':
            return left_sibling
        else: return right_sibling




class BPlusTree:
    def __init__(self, branching_factor=16):
        self.root = Node(branching_factor)
        self.t = branching_factor

    def __setitem__(self, key, value):
        self.insert(key,value)

    def find_leaf(T, key):
        cur = T.root
        while cur.leaf != True:
            for i in range(0,cur.key_num+1):
            #for i = 0 to cur.key_num
                if i == cur.key_num or key < cur.key[i]:
                    cur = cur.child[i]
                    break
        return cur

    def split(T, node: Node):
        new_node = Node(T.t, node.leaf)                 #Создаем новый узел
    
        # Перенаправляем right и left указатели
        new_node.right = node.right
        node.right.left = new_node
        node.right = new_node
        new_node.left = node
    
        # Перемещаем t - 1 значений и соответствующих им указателей в new_node
        mid_key = node.key[T.t]
        new_node.key_num = T.t - 1
        node.key_num = T.t
        for i in range(new_node.key_num):
        #for i = 0 to new_node.key_num - 1
            new_node.key[i] = node.key[i + T.t + 1]
            new_node.pointers[i] = node.pointers[i + T.t + 1]  
            new_node.child[i] = node.child[i + T.t + 1]
            if node.child[i+T.t+1]: node.child[i+T.t+1].parent = new_node
        new_node.child[new_node.key_num] = node.child[2 * T.t]
        if node.child[2 * T.t]: node.child[2 * T.t].parent = new_node
    
        if node.leaf:
            new_node.key_num += 1
            new_node.leaf = True
        
            # Перемещаем в new_node оставшийся при разбиении элемент mid_key 
            #for i = new_node.key_num - 1 downto 1
            for i in range(new_node.key_num-1,0,-1):
                new_node.key[i] = new_node.key[i - 1]
                new_node.pointers[i] = new_node.pointers[i - 1]
            new_node.key[0] = node.key[T.t]
            new_node.pointers[0] = node.pointers[T.t]
    
        if node == T.root:
            T.root = Node(T.t, False)                  # Создаем новый корень T.root 
            T.root.key[0] = mid_key
            T.root.child[0] = node
            T.root.child[1] = new_node
            T.root.key_num = 1;
            node.parent = T.root
            new_node.parent = T.root
        else:
            new_node.parent = node.parent
            parent = node.parent
        
            # Ищем позицию mid_key в отце 
            pos = 0
            while pos < parent.key_num and parent.key[pos] < mid_key:
                pos += 1
        
            # Добавляем mid_key в отца и направляем ссылку из него на new_node
            for i in range(parent.key_num,pos,-1): 
            #for i = parent.key_num downto pos + 1 
                parent.key[i] = parent.key[i - 1]
            for i in range(parent.key_num+1,pos+1,-1):
            #for i = parent.key_num + 1 downto pos + 2 
                parent.child[i] = parent.child[i - 1]
            parent.key[pos] = mid_key
            parent.child[pos + 1] = new_node
            parent.key_num += 1
        
            if parent.key_num == 2 * T.t:
                T.split(parent)
    
    
                
    def insert(T, key, value):
        leaf = T.find_leaf(key)
        if leaf.contains(key):
           return False
    
        #Ищем позицию для нового ключа 
        pos = 0
        while pos < leaf.key_num and leaf.key[pos] < key:
            pos += 1
      
        #Вставляем ключ
        #for i = leaf.key_num downto pos + 1 
        for i in range(leaf.key_num, pos,-1):
            leaf.key[i] = leaf.key[i - 1]
            leaf.pointers[i] = leaf.pointers[i - 1]
        leaf.key[pos] = key
        leaf.pointers[pos] = value
        leaf.key_num += 1
    
        if leaf.key_num == 2 * T.t:              #t — степень дерева
            T.split(leaf)                   #Разбиваем узел
        return True

    def update(T, tec: Node):
        if tec == T.root:
            return None
        parent = tec.parent
        i = 0
        while (i < parent.key_num and (parent.child[i].key_num > 0 and parent.key[i] > parent.child[i].key[parent.child[i].key_num-1]) and
            (parent.child[i+1].key_num > 0 and parent.key[i] <= parent.child[i+1].key[0])):
           i += 1
        l_child = parent.child[i]
        r_child = parent.child[i+1]
        if tec.leaf == True:
            #if merging happened then nothing should be done
            #below is handling transfering
            if(l_child and l_child.key_num > 0 and l_child.key[l_child.key_num-1] >= parent.key[i]):
                parent.key[i] = r_child.key[0]
            elif(r_child and r_child.key_num > 0 and r_child.key[0] < parent.key[i]):
                parent.key[i] = r_child.key[0]
        else:
            #handling non-leaf transformations
            if r_child and r_child.key_num == 0 and i < parent.key_num:
                transfered = parent.key[i]
                pos = tec.key_num
                while pos > 0 and tec.key[pos-1] >= parent.key[i]:
                    tec.key[pos] = tec.key[pos-1]
                    pos -= 1
                tec.key[pos] = parent.key[i]
                tec.key_num += 1
                r_child.key[0] = transfered
            else:
                if(l_child and l_child.key_num > 0 and l_child.key[l_child.key_num-1] >= parent.key[i]):
                    parent.key[i],l_child.key[l_child.key_num-1] = l_child.key[l_child.key_num-1],parent.key[i]
                elif (r_child and r_child.key_num > 0 and r_child.key[0] < parent.key[i]):
                    parent.key[i],r_child.key[0] = r_child.key[0],parent.key[i]

    def delete_in_node(T, tec: Node, key):
        if not(tec.contains(key)):
            return None
     
        # Ищем позицию удаляемого ключа 
        pos = 0
        while pos < tec.key_num and tec.key[pos] < key:
            pos += 1

        min_key = tec.key[0]
        # Удаляем ключ
        #for i = pos to tec.key_num - 1
        for i in range(pos, tec.key_num): 
            tec.key[i] = tec.key[i + 1]
            tec.pointers[i] = tec.pointers[i + 1]
        #for i = pos + 1 to tec.key_num
        for i in range(pos+1,tec.key_num+1):
            tec.child[i] = tec.child[i + 1]
            
        tec.key_num -= 1

        if tec.key_num < T.t - 1:
            right_sibling = tec.get_sibling('right')
            left_sibling = tec.get_sibling('left')
            if left_sibling and (left_sibling.key_num > T.t - 1):
                left_sibling.key_num -= 1
                tec.key_num += 1
     
                #Перемещаем максимальный из left_sibling ключ на первую позицию в tec 
                #for i = 1 to tec.key_num - 1
                for i in range(tec.key_num-1,0):
                    tec.key[i] = tec.key[i - 1]
                    tec.pointers[i] = tec.pointer[i - 1] 
                    tec.child[i] = tec.child[i - 1]
                tec.child[tec.key_num] = tec.child[tec.key_num - 1]

                tec.key[0] = left_sibling.key[left_sibling.key_num]
                tec.pointers[0] = left_sibling.pointers[left_sibling.key_num]
                tec.child[0] = left_sibling.child [left_sibling.key_num + 1]
                if(left_sibling.child [left_sibling.key_num + 1]): left_sibling.child [left_sibling.key_num + 1].parent = tec

                T.update(tec) #Обновить ключи на пути к корню

            elif right_sibling and (right_sibling.key_num > T.t - 1):
                right_sibling.key_num -= 1
                tec.key_num += 1
     
                # Перемещаем минимальный из right_sibling ключ на последнюю позицию в tec 
                tec.key[tec.key_num - 1] = right_sibling.key[0]
                tec.pointers[tec.key_num - 1] = right_sibling.pointers[0]
                #tec.child[tec.key_num - 1] = right_sibling.child[0]
                tec.child[tec.key_num] = right_sibling.child[0]
                if (right_sibling.child[0]): right_sibling.child[0].parent = tec

                for i in range(right_sibling.key_num):
                    right_sibling.key[i] = right_sibling.key[i+1]
                    right_sibling.pointers[i] = right_sibling.pointers[i+1] 
                    right_sibling.child[i] = right_sibling.child[i+1]
                right_sibling.child[right_sibling.key_num] = right_sibling.child[right_sibling.key_num+1]

                T.update(tec)#Обновить ключи на пути к корню

            else:
                #merging
                if left_sibling is not None: 
                    #Сливаем tec и left_sibling
                    for i in range(tec.key_num):
                    #for i = 0 to tec.key_num - 1
                        left_sibling.key[left_sibling.key_num] = tec.key[i]
                        left_sibling.pointers[left_sibling.key_num] = tec.pointers[i]
                        left_sibling.child[left_sibling.key_num + 1] = tec.child[i]
                        if(tec.child[i]): tec.child[i].parent = left_sibling
                        left_sibling.key_num += 1
                    left_sibling.child[left_sibling.key_num + 1] = tec.child[tec.key_num]
                    if tec.child[tec.key_num] : tec.child[tec.key_num].parent = left_sibling
                    
                    tec.key_num = 0
                    #Перенаправляем right и left указатели
                    left_sibling.right = tec.right
                    tec.right.left = left_sibling 
                
                    T.update(left_sibling) #Обновить ключи на пути к корню
                    #T.delete_in_node(left_sibling.parent, min_key(tec))
                    T.delete_in_node(left_sibling.parent, min_key)
                    #Удаляем разделительный ключ в отце
                elif right_sibling is not None:
                    #Сливаем tec и right_sibling
                    #for i = 0 to tec.key_num - 1
                    for i in range(right_sibling.key_num):
                        tec.key[tec.key_num] = right_sibling.key[i]
                        tec.pointers[tec.key_num] = right_sibling.pointers[i]
                        tec.child[tec.key_num + 1] = right_sibling.child[i]
                        if(right_sibling.child[i]): right_sibling.child[i].parent = tec
                        tec.key_num += 1
                    tec.child[tec.key_num + 1] = right_sibling.child[right_sibling.key_num]
                    if(right_sibling.child[right_sibling.key_num]) : right_sibling.child[right_sibling.key_num].parent = tec
                 
                    right_sibling.key_num = 0
                    #Перенаправляем right и left указатели
                    right_sibling.right.left = tec
                    tec.right = right_sibling.right
                 
                    T.update(tec)  #Обновить ключи на пути к корню

                    #T.delete_in_node(tec.parent, min_key(right_sibling))
                    T.delete_in_node(tec.parent, right_sibling.key[0])
                    #Удаляем разделительный ключ в отце
            if (T.root.key_num == 1 and T.root.child[1].key_num == 0) or T.root.key_num == 0:
                T.root = T.root.child[0]

            
    def print(T, blocks: list):
        newBlocks = []

        for cur in blocks:

            print("[|",end="")
            if(cur.leaf):
                for j in range(cur.key_num):
                    print(cur.pointers[j],"|",end="")
            else:
                j = 0
                while j < cur.key_num: 
                    #traverse the childBlocks, print values and save all the childBlocks
                    key = cur.key[j]
                    print(key,"|",end="")
                    if(cur.child[j] is not None):
                        newBlocks.append(cur.child[j])
                    j += 1
              
                if cur.child[j] is not None:
                    newBlocks.append(cur.child[j])
            
            print("]  ",end="")

        if(len(newBlocks) == 0): 
            #if there is no childBlock block left to send out then just the end of the recursion
            print('\n')
        else:
            print('\n')
            T.print(newBlocks)

    def delete(T, key):
        leaf = BPlusTree.find_leaf(T,key)
        if not(leaf.contains(key)):
            return False
        else:
            T.delete_in_node(leaf, key)  #Удалить ключ из вершины
            return True

class BPlusDot(BPlusTree):
    def print_viz(self):
        dot = Digraph(comment='BPlus Tree visualization')
        #dot.body.append('graph[rankdir=RL]\n')
        dot.body.append('node[shape=record]\n')
        self.print_content([self.root],dot)
        dot.format = 'png'
        dot.render('output_data/output', view=True, cleanup=True)
        #dot.render(view=True, cleanup=True)
        file = open('output_data/test.txt','w')
        file.write(dot.source)
        file.close()
        #print(dot.source)
    def print_content(self, blocks: list, dot):
        newBlocks = []

        for cur in blocks:
            cur_name = str(id(cur))
            if(cur.leaf):
                node_label = '{'
                for i in range(cur.key_num-1):
                    tmp = '{%s|%s}|' % (cur.key[i], cur.pointers[i])
                    node_label += tmp
                node_label += '{%s|%s}}' % (cur.key[cur.key_num-1], cur.pointers[cur.key_num-1])
                dot.node(cur_name,label=node_label)
            else:
                node_label=''

                for j in range(cur.key_num):
                    node_label += '<ch{}>|{}|'.format(j,cur.key[j])
                node_label += '<ch{}>*'.format(cur.key_num)
                dot.node(cur_name,label=node_label+'')
                j = 0
                while j < cur.key_num:
                    #traverse the childBlocks, print values and save all the childBlocks
                    key = cur.key[j]

                    if(cur.child[j] is not None):
                        dot.edge(cur_name + ':ch%d'% j,str(id(cur.child[j]))  + ':ch0')
                        newBlocks.append(cur.child[j])
                    j += 1
              
                if cur.child[j] is not None:
                    dot.edge(cur_name + ':ch%d'% j,str(id(cur.child[j])) + ':ch0')
                    newBlocks.append(cur.child[j])

        dot.body.append('\n\n')
        if(len(newBlocks) > 0): 
            self.print_content(newBlocks,dot)
            
        
            

