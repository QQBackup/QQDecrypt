// .vitepress/theme/index.ts
import { h } from 'vue'
import DefaultTheme from 'vitepress/theme'
import HashCalculator from './components/HashCalculator.vue'
import { inject as vercelInject } from "@vercel/analytics" // 使用通用包
import './style.css'
import { Theme } from 'vitepress' // 确保导入 Theme 类型

export default {
  ...DefaultTheme,
  enhanceApp({ app }) {
    // 注册全局组件
    app.component('HashCalculator', HashCalculator)

    // 仅在生产环境中注入 Vercel Analytics
    if (process.env.NODE_ENV === 'production') {
      vercelInject({
        id: 'prj_87NykKrzbGHfoLWeerHSJv031hsJ'
      })
    }
  }
} satisfies Theme
