---
layout: page
title: 贡献者
description: 为网站内容做出贡献的成员
sidebar: false
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


const contributors = [
  {
    avatar: "https://ooo.0x0.ooo/2024/10/07/O4wGIc.jpg",
    name: "Raincarnator",
    title: "贡献者",
    desc: '提交了 <a href="https://github.com/QQBackup/QQDecrypt/pull/1#issue-2568844396" target="_blank">PR #1</a>: docs: add more information',
    links: [
      { icon: 'github', link: "https://github.com/Raincarnator" }
    ]
  },

  {
    avatar: "https://ooo.0x0.ooo/2024/11/16/OHL7jx.png",
    name: "Wenz-jam",
    title: "贡献者",
    desc: '提交了 <a href="https://github.com/QQBackup/qq-win-db-key/pull/46" target="_blank">PR #46</a>:添加一种linux下获取密钥的方式',
    links: [
      { icon: 'github', link: "https://github.com/Wenz-jam" }
    ]
  },
  
  {
    avatar: "https://ooo.0x0.ooo/2025/01/04/OEHG9B.jpg",
    name: "Dao1023",
    title: "贡献者",
    desc: '<a href="https://github.com/QQBackup/qq-win-db-key/issues/50" target="_blank">issues #50</a>:补充NTQQ(Windows)教程',
    links: [
      { icon: 'github', link: "https://github.com/Dao1023" }
    ]
  },  

]
</script>

<VPTeamPage>

  <VPTeamPageTitle>
    <template #title>
      仓库成员
    </template>
    <template #lead>
      若需要修改/增删信息可在仓库发起 PR 或通过 <a href="mailto:issues@sbcnm.top">issues@sbcnm.top</a> 联系我修改
    </template>
  </VPTeamPageTitle>
  
  <VPTeamMembers :members="members" />

  <VPTeamPageTitle>
    <template #title>
       仓库贡献者
    </template>
    <template #lead>
      这些成员为项目做出了贡献
    </template>
  </VPTeamPageTitle>
  
  <VPTeamMembers :members="contributors" />
</VPTeamPage>
