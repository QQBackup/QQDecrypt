---
layout: page
---

<!-- markdownlint-disable MD033 MD041 -->
<script setup>
import {
  VPTeamPage,
  VPTeamPageTitle,
  VPTeamMembers
} from 'vitepress/theme'

// 定义成员信息
const members = [
  {
    avatar: "/head/Young-Lord.jpg",
    name: "Young Lord",
    title: "开发者",
    desc: "高考，所有项目2025年8月前不维护。愿意接手请联系下方邮箱。",
    links: [
      { icon: 'github', link: "https://github.com/Young-Lord" }
    ]
  },
  {
    avatar: "/head/Ljzd-PRO.jpg",
    name: "Ljzd PRO",
    title: "开发者",
    desc: "暂无个人简介",
    links: [
      { icon: 'github', link: "https://github.com/Ljzd-PRO" }
    ]
  },
  {
    avatar: "/head/shenjackyuanjie.jpg",
    name: "Shen Jack",
    title: "开发者",
    desc: "happy lazy |HWS with me |要寄了(不是) 2025年8月之前不保证任何项目维护（你知道的，高考）",
    links: [
      { icon: 'github', link: "https://github.com/shenjackyuanjie" }
    ]
  },
  {
    avatar: "/head/leng-yue.jpg",
    name: "Leng Yue",
    title: "开发者",
    desc: "Push the boundary of artificial general intelligence.",
    links: [
      { icon: 'github', link: "https://github.com/leng-yue" }
    ]
  },
  {
    avatar: "/head/fumiama.jpg",
    name: "Fumiama",
    title: "开发者",
    desc: "千载何方归梦，棹舟星河波开。",
    links: [
      { icon: 'github', link: "https://github.com/fumiama" }
    ]
  },
  {
    avatar: "/head/alphagocc.jpg",
    name: "Alpha Gocc",
    title: "开发者",
    desc: "Alphagocc",
    links: [
      { icon: 'github', link: "https://github.com/alphagocc" }
    ]
  },
  {
    avatar: "/head/Mythologyli.jpg",
    name: "Mythology Li",
    title: "开发者",
    desc: "Embedded Systems, Robotics, Graphing Calculators and Minecraft!",
    links: [
      { icon: 'github', link: "https://github.com/Mythologyli" }
    ]
  },
  {
    avatar: "/head/yllhwa.jpg",
    name: "Yllhwa",
    title: "开发者",
    desc: "暂无个人简介",
    links: [
      { icon: 'github', link: "https://github.com/yllhwa" }
    ]
  },
  {
    avatar: "/head/siten.jpg",
    name: "Siten",
    title: "开发者",
    desc: "暂无个人简介",
    links: [
      { icon: 'github', link: "https://github.com/siten" }
    ]
  }
]
</script>

<VPTeamPage>
  <VPTeamPageTitle>
    <template #title>
      仓库贡献者
    </template>
    <template #lead>
      若需要修改/增删信息可在仓库发起pr或通过 <a href="mailto:issues@sbcnm.top">issues@sbcnm.top</a> 联系我修改
    </template>
  </VPTeamPageTitle>
  
  <VPTeamMembers :members="members" />
</VPTeamPage>
