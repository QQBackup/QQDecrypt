// .vitepress/theme/index.ts
import { h } from 'vue'
import DefaultTheme from 'vitepress/theme'
import HashCalculator from './components/HashCalculator.vue'
import { Theme } from 'vitepress' 
import './style/index.css'
import "vitepress-markdown-timeline/dist/theme/index.css";


export default {
  ...DefaultTheme,
  enhanceApp({ app }) {
    // 注册全局组件
    app.component('HashCalculator', HashCalculator)  

  }
} satisfies Theme