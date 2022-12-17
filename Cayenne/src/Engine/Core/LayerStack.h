#include <cayennepch.h>
#include <Engine/Core/core.h>
#include "Layer.h"


#ifndef CAYENNE_LAYERSTACK_H
#define CAYENNE_LAYERSTACK_H

namespace Cayenne {
    struct LayerStackNode
    {
        Layer* data;
        LayerStackNode* next = nullptr;

        LayerStackNode(Layer* l) : data(l) {}

        struct iterator
        {
            iterator(LayerStackNode* ptr) : m_ptr(ptr) {}

            LayerStackNode& operator*() const { return *m_ptr; }
            LayerStackNode* operator->() { return m_ptr; }
            iterator& operator++() { m_ptr++; return *this; }
            iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
            friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };
        private:
            LayerStackNode* m_ptr;
        };
    };

    class CY_API LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}



#endif //CAYENNE_LAYERSTACK_H
