/* SPDX-License-Identifier: (BSD-3-Clause OR LGPL-2.1) */
#ifndef _PMUCTL_H
#define _PMUCTL_H

#define PMUCTL_IOC_MAGIC	0xF1

/* List of PMU controls enabled by the driver. */
enum pmu_ctls {
	PM_CTL_PMCCNTR, /* Enable/disable PMCCNTR_EL0 */
	PM_CTL_CNTKCTL, /* Enable Physical Timer Control EL0 access */
	PM_CTL_CNT, /* Keep this last! */
};

struct pmuctl_pmccntr_data {
	int enable; /* 0 - disable, 1 - enable */
};

#define PMU_IOC_PMCCNTR \
	_IOW(PMUCTL_IOC_MAGIC, PM_CTL_PMCCNTR, struct pmuctl_pmccntr_data)
#define PMU_IOC_CNTKCTL \
	_IOW(PMUCTL_IOC_MAGIC, PM_CTL_CNTKCTL, struct pmuctl_pmccntr_data)


#endif
