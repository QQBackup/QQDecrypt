// .vitepress/theme/index.ts
import { h } from 'vue'
import DefaultTheme from 'vitepress/theme'
import HashCalculator from './components/HashCalculator.vue'
import { onMounted, watch, nextTick } from 'vue'
import { useRoute } from 'vitepress'
import mediumZoom from 'medium-zoom'
import { Theme } from 'vitepress' 
import './style/index.css'
import "vitepress-markdown-timeline/dist/theme/index.css";


export default {
  ...DefaultTheme,
   setup() {
    const route = useRoute()
    const initZoom = () => {
      // 为所有图片增加缩放功能
      mediumZoom('.main img', { background: 'var(--vp-c-bg)' })
    }
    onMounted(() => {
      initZoom()
    })
    watch(
      () => route.path,
      () => nextTick(() => initZoom())
    )
  }, 
  enhanceApp({ app }) {
    // 注册全局组件
    app.component('HashCalculator', HashCalculator)  

  }
} satisfies Theme